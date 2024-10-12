#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include "metrics.h"

// Enum para definir as cores dos nós
enum Color
{
    RED,
    BLACK
};

// Estrutura do nó da Red-Black Tree
template <typename TKey, typename TValue>
struct Node
{
    TKey id;                  // Chave genérica
    TValue fileLocation;       // Valor genérico associado à chave
    bool color;                // Cor do nó (Vermelho ou Preto)
    Node *left, *right, *parent; // Ponteiros para os filhos e o pai

    // Construtor para inicializar o nó
    Node(TKey id, TValue fileLocation)
    {
        this->id = id;
        this->fileLocation = fileLocation;
        left = right = parent = nullptr;
        this->color = RED; // Nós são vermelhos por padrão na inserção
    }
};

// Classe Red-Black Tree
template <typename TKey, typename TValue>
class RedBlackTree
{
private:
    Node<TKey, TValue> *root;  // Raiz da árvore
    Node<TKey, TValue> *TNULL; // Nó nulo usado para representar folhas

    // Função auxiliar privada para excluir subárvores
    void deleteSubTree(Node<TKey, TValue> *node);

    // Funções auxiliares privadas
    void initializeNULLNode(Node<TKey, TValue> *node, Node<TKey, TValue> *parent);
    void preOrderHelper(Node<TKey, TValue> *node);
    Node<TKey, TValue> *searchTreeHelper(Node<TKey, TValue> *node, TKey key, Metrics *metrics = nullptr, int metricsId = -1);
    void fixInsert(Node<TKey, TValue> *k);
    void leftRotate(Node<TKey, TValue> *x);
    void rightRotate(Node<TKey, TValue> *x);

public:
    // Construtor
    RedBlackTree();

    // Destrutor
    ~RedBlackTree();  // <- Declarado o destrutor

    // Funções públicas
    void insert(TKey key, TValue fileLocation, Metrics *metrics = nullptr, int metricsId = -1);
    bool search(TKey key, Metrics *metrics = nullptr, int metricsId = -1);
    void printTree();
};

#include "RedBlackTree.tpp" // Implementação no arquivo .tpp

#endif // REDBLACKTREE_H
