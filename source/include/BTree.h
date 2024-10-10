#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <vector>
#include "metrics.h"

// Classe de nós da árvore B
template <typename TKey, typename TValue>
class BTreeNode
{
public:
    TKey *keys;           // Array de chaves
    TValue *values;        // Array de valores associados às chaves
    int t;                // Grau mínimo da árvore
    BTreeNode **children;  // Array de ponteiros para filhos
    int n;                // Número atual de chaves
    bool leaf;            // Se o nó é uma folha ou não

    BTreeNode(int t, bool leaf); // Construtor

    // Destrutor
    ~BTreeNode();  // <- Destrutor declarado

    // Funções da árvore B
    void insertNonFull(TKey key, TValue value);
    void splitChild(int i, BTreeNode *y);
    BTreeNode *search(TKey key, Metrics *metrics = nullptr, int metricsId = -1);
    void traverse();

    template <typename K, typename V>
    friend class BTree;
};

// Classe da árvore B
template <typename TKey, typename TValue>
class BTree
{
private:
    BTreeNode<TKey, TValue> *root; // Ponteiro para a raiz
    int t;                         // Grau mínimo da árvore B

    // Função auxiliar privada para excluir subárvores
    void deleteSubTree(BTreeNode<TKey, TValue> *node);  // <- Declarada a função deleteSubTree

public:
    BTree(int t);  // Construtor

    // Destrutor
    ~BTree();  // <- Destrutor declarado

    // Funções públicas
    void insert(TKey key, TValue value, Metrics *metrics = nullptr, int metricsId = -1);
    bool search(TKey key, Metrics *metrics = nullptr, int metricsId = -1);
    void traverse();
};

#include "BTree.tpp" // Inclui a implementação

#endif // BTREE_H
