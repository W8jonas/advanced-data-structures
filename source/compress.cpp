#include "huffman.h"
#include "fileManager.h"
#include <iostream>

void menu()
{
    std::cout << "Escolha uma opção:\n";
    std::cout << "1. Comprimir N overviews\n";
    std::cout << "2. Descomprimir overviewComp.bin\n";
    std::cout << "3. Sair\n";
}

int main(int argc, char *argv[])
{
    Huffman huffman;
    int option;
    int N;
    std::string compressedFile = "overviewComp.bin";
    std::string decompressedFile = "overviewDecomp.txt";

    std::string entryPath = "";
    if (argc > 1)
    {
        entryPath = argv[1];
        std::cout << "Valor recebido: " << entryPath << std::endl;
    }
    else
    {
        std::cout << "Nenhum valor foi passado como parâmetro!" << std::endl;
        return 1;
    }

    do
    {
        menu();
        std::cin >> option;

        if (option == 1)
        {
            std::cout << "Digite o número de overviews para comprimir: ";
            std::cin >> N;

            fileManager fm(entryPath);
            // Escreve o resumo dos N filmes no arquivo compressedFile
            fm.saveRandomOverviewsToBinary(compressedFile, N);

            // Compressão
            huffman.compress(compressedFile, compressedFile);
            std::cout << "Compressão concluída. Arquivo salvo em " << compressedFile << "\n";
        }
        else if (option == 2)
        {
            // Descompressão
            huffman.decompress(compressedFile, decompressedFile);
            std::cout << "Descompressão concluída. Arquivo salvo em " << decompressedFile << "\n";
        }
    } while (option != 3);

    return 0;
}
