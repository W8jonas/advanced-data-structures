#include "huffman.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <queue>

// Função auxiliar para liberar a árvore de Huffman
void Huffman::deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Função que constrói a árvore de Huffman
Node* Huffman::buildHuffmanTree(const std::unordered_map<char, int>& freq) {
    auto cmp = [](Node* left, Node* right) { return left->freq > right->freq; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> pq(cmp);

    for (const auto& pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }

    return pq.top();
}

// Função que gera os códigos de Huffman
void Huffman::generateCodes(Node* root, const std::string& str, std::unordered_map<char, std::string>& huffmanCode) {
    if (root == nullptr) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}

// Função de compressão
void Huffman::compress(const std::string& binaryFile, const std::string& compressedFile) {
    std::unordered_map<char, int> freq;

    // Lê o arquivo binário e calcula a frequência dos caracteres
    std::ifstream input(binaryFile, std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "Erro ao abrir o arquivo binário para compressão.\n";
        return;
    }

    char character;
    while (input.get(character)) {
        freq[character]++;
    }
    input.close();

    Node* root = buildHuffmanTree(freq);
    std::unordered_map<char, std::string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    // Grava o arquivo comprimido
    std::ofstream output(compressedFile, std::ios::binary);
    if (!output.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para salvar a compressão.\n";
        return;
    }

    // Grava o cabeçalho contendo a frequência dos caracteres
    for (const auto& pair : freq) {
        output.write(reinterpret_cast<const char*>(&pair.first), sizeof(pair.first));
        output.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
    }
    output.put('\0'); // Delimitador de fim do cabeçalho

    // Codifica o conteúdo
    input.open(binaryFile, std::ios::binary);
    std::string encodedString;
    while (input.get(character)) {
        encodedString += huffmanCode[character];
    }
    input.close();

    // Agrupa os bits em bytes e grava no arquivo
    int bitCount = 0;
    unsigned char byte = 0;
    for (char bit : encodedString) {
        byte = (byte << 1) | (bit - '0');
        bitCount++;
        if (bitCount == 8) {
            output.put(byte);
            byte = 0;
            bitCount = 0;
        }
    }
    if (bitCount > 0) {  // Se sobrarem bits não agrupados
        byte <<= (8 - bitCount);
        output.put(byte);
    }

    output.close();

    // Libera a memória da árvore de Huffman
    deleteTree(root);
}

// Função de descompressão
void Huffman::decompress(const std::string& compressedFile, const std::string& decompressedFile) {
    std::ifstream input(compressedFile, std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "Erro ao abrir o arquivo comprimido.\n";
        return;
    }

    std::unordered_map<char, int> freq;
    char character;
    int frequency;

    // Lê o cabeçalho contendo a frequência dos caracteres
    while (input.read(reinterpret_cast<char*>(&character), sizeof(character))) {
        if (character == '\0') break;  // Fim do cabeçalho
        input.read(reinterpret_cast<char*>(&frequency), sizeof(frequency));
        freq[character] = frequency;
    }

    Node* root = buildHuffmanTree(freq);

    // Lê o corpo do arquivo comprimido
    std::string encodedString;
    char byte;
    while (input.get(byte)) {
        for (int i = 7; i >= 0; --i) {
            encodedString += ((byte >> i) & 1) ? '1' : '0';
        }
    }
    input.close();

    // Decodifica os bits
    std::ofstream output(decompressedFile, std::ios::binary);
    if (!output.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para salvar a descompressão.\n";
        return;
    }

    Node* currentNode = root;
    for (char bit : encodedString) {
        if (bit == '0') {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }

        if (!currentNode->left && !currentNode->right) {
            output.put(currentNode->ch);
            currentNode = root;
        }
    }

    output.close();

    // Libera a memória da árvore de Huffman
    deleteTree(root);
}
