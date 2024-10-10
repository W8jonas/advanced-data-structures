#include <iostream>
#include <chrono>
#include <cassert>

#include "BTree.h"

using namespace std;
using namespace std::chrono;

void test_insertion(BTree<int, int> &tree)
{
    double timeTaken = 0.0;

    // Inserção de valores na árvore com medição de comparações e tempo
    int values[] = {10, 20, 30, 15, 25, 5, 1};
    for (int i = 0; i < 7; i++)
    {
        auto start = high_resolution_clock::now();  // Começa a contagem do tempo
        tree.insert(values[i], values[i]);
        auto stop = high_resolution_clock::now();   // Finaliza a contagem
        auto duration = duration_cast<microseconds>(stop - start);
        timeTaken = duration.count();

        cout << "Valor " << values[i] << " inserido "
             << ", Tempo de inserção: " << timeTaken << " microsegundos" << endl;
    }

    // Testa se todos os valores foram inseridos
    assert(tree.search(10));
    assert(tree.search(20));
    assert(tree.search(30));
    assert(tree.search(15));
    assert(tree.search(25));
    assert(tree.search(5));
    assert(tree.search(1));

    cout << "Teste de inserção da B-Tree passou!" << endl;
}

void test_search(BTree<int, int> &tree)
{

    // Testa busca de valores que estão na árvore
    int values[] = {10, 20, 30, 15, 25, 5, 1};
    for (int i = 0; i < 7; i++)
    {
        bool found = tree.search(values[i]);
        assert(found);
        cout << "Valor " << values[i] << " encontrado" << endl;
    }

    // Testa busca de valor que não está na árvore
    int missingValue = 100;
    bool found = tree.search(missingValue);
    assert(!found);
    cout << "Valor " << missingValue << " não encontrado" << endl;

    cout << "Teste de busca da B-Tree passou!" << endl;
}

int main(int argc, char **argv)
{
    BTree<int, int> tree(3); // Grau mínimo t = 3

    // Testes de inserção
    test_insertion(tree);

    // Testes de busca
    test_search(tree);

    return 0;
}
