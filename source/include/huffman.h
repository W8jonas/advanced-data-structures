#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>

// Estrutura para os nós da árvore de Huffman
struct Node {
    char ch;  // Caractere armazenado
    int freq; // Frequência do caractere
    Node* left; // Filho esquerdo
    Node* right; // Filho direito

    Node(char character, int frequency, Node* leftChild = nullptr, Node* rightChild = nullptr)
        : ch(character), freq(frequency), left(leftChild), right(rightChild) {}
};

class Huffman {
public:
    void compress(const std::string& binaryFile, const std::string& compressedFile);
    void decompress(const std::string& compressedFile, const std::string& decompressedFile);

private:
    void deleteTree(Node* root);
    Node* buildHuffmanTree(const std::unordered_map<char, int>& freq);
    void generateCodes(Node* root, const std::string& str, std::unordered_map<char, std::string>& huffmanCode);
};

#endif // HUFFMAN_H
