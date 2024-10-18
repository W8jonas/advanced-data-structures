#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "fileManager.h"
#include "metrics.h"
#include "RedBlackTree.h"
#include "BTree.h"
#include "film.h"

int main(int argc, char *argv[])
{
    std::string entryPath = "";
    if (argc > 1)
    {
        entryPath = argv[1];
    }
    else
    {
        std::cout << "Nenhum valor foi passado como parâmetro!" << std::endl;
        return 1;
    }

    fileManager fileManager(entryPath);
    std::vector<std::string> inputDataString = fileManager.getFileRead("compara_tree.dat");
    std::vector<int> inputData;

    // Converte vetor de strings para vetor de inteiros
    for (const auto &str : inputDataString)
    {
        inputData.push_back(std::stoi(str));
    }

    Metrics metrics;

    // Número de execuções e registros
    const int M = 3;     // Execuções
    const int N = 20000; // Registros
    const int B = 10000; // Registros buscados

    std::ostringstream resultStream;

    for (int run = 0; run < M; run++)
    {
        std::vector<Film> filmsForRedBlack;
        fileManager.getRandomNFilms(N, filmsForRedBlack);

        std::ostringstream blockStream;
        blockStream << "Red-Black Tree (run: " << run << ")\n";
        blockStream << "registros inseridos: " << N << "\n";
        blockStream << "registros buscados: " << B << "\n";
        blockStream << "execuções: " << M;

        auto redBlackTreeId = metrics.createBlock(blockStream.str());

        RedBlackTree<int, Film> redBlackTree;

        // Inserção na Árvore Rubro-Negra
        metrics.startTimer(redBlackTreeId);
        for (const auto &film : filmsForRedBlack)
        {
            redBlackTree.insert(film.databaseId, film, &metrics, redBlackTreeId);
        }
        metrics.stopTimer(redBlackTreeId);

        // Busca na Árvore Rubro-Negra
        auto searchId = metrics.createBlock("Search");
        metrics.startTimer(searchId);
        for (int i = 0; i < B; i++)
        {
            redBlackTree.search(filmsForRedBlack[i % N].databaseId, &metrics, searchId);
        }
        metrics.stopTimer(searchId);
    }

    for (int run = 0; run < M; run++)
    {
        std::vector<Film> filmsForBTree;
        fileManager.getRandomNFilms(N, filmsForBTree);

        std::ostringstream blockStream;
        blockStream << "Árvore B (Ordem: 20) (run: " << run << ")\n";
        blockStream << "registros inseridos: " << N << "\n";
        blockStream << "registros buscados: " << B << "\n";
        blockStream << "execuções: " << M;

        auto bTreeId20 = metrics.createBlock(blockStream.str());

        BTree<int, Film> bTree20(20);
        metrics.startTimer(bTreeId20);
        for (const auto &film : filmsForBTree)
        {
            bTree20.insert(film.databaseId, film, &metrics, bTreeId20);
        }
        metrics.stopTimer(bTreeId20);

        // Busca na B-Tree
        auto searchBTreeId = metrics.createBlock("Search");
        metrics.startTimer(searchBTreeId);
        for (int i = 0; i < B; i++)
        {
            bTree20.search(filmsForBTree[i % N].databaseId, &metrics, searchBTreeId);
        }
        metrics.stopTimer(searchBTreeId);
    }

    for (int run = 0; run < M; run++)
    {
        std::vector<Film> filmsForBTree;
        fileManager.getRandomNFilms(N, filmsForBTree);

        std::ostringstream blockStream;
        blockStream << "Árvore B (Ordem: 200) (run: " << run << ")\n";
        blockStream << "registros inseridos: " << N << "\n";
        blockStream << "registros buscados: " << B << "\n";
        blockStream << "execuções: " << M;

        auto bTreeId200 = metrics.createBlock(blockStream.str());

        BTree<int, Film> bTree200(200);
        // Inserção na B-Tree
        metrics.startTimer(bTreeId200);
        for (const auto &film : filmsForBTree)
        {
            bTree200.insert(film.databaseId, film, &metrics, bTreeId200);
        }
        metrics.stopTimer(bTreeId200);

        // Busca na B-Tree
        auto searchBTreeId200 = metrics.createBlock("Search");
        metrics.startTimer(searchBTreeId200);
        for (int i = 0; i < B; i++)
        {
            bTree200.search(filmsForBTree[i % N].databaseId, &metrics, searchBTreeId200);
        }
        metrics.stopTimer(searchBTreeId200);
    }

    std::string results = metrics.getFormattedResults();
    fileManager.writeFile("compara_tree_2.out", results);

    return 0;
}
