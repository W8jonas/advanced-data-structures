#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

template <typename TKey, typename TValue>
void RedBlackTree<TKey, TValue>::initializeNULLNode(Node<TKey, TValue> *node, Node<TKey, TValue> *parent)
{
  node->id = TKey();
  node->fileLocation = TValue();
  node->parent = parent;
  node->left = nullptr;
  node->right = nullptr;
  node->color = BLACK;
}

template <typename TKey, typename TValue>
void RedBlackTree<TKey, TValue>::preOrderHelper(Node<TKey, TValue> *node)
{
  if (node != TNULL)
  {
    cout << node->id << " ";
    preOrderHelper(node->left);
    preOrderHelper(node->right);
  }
}

template <typename TKey, typename TValue>
Node<TKey, TValue> *RedBlackTree<TKey, TValue>::searchTreeHelper(Node<TKey, TValue> *node, TKey key, Metrics *metrics, int metricsId)
{
  if (node == TNULL || key == node->id)
  {
    return node;
  }
  if (metrics != nullptr)
  {
    metrics->addComparisons(metricsId); // Contabiliza uma comparação
  }
  if (key < node->id)
  {
    return searchTreeHelper(node->left, key, metrics, metricsId);
  }
  return searchTreeHelper(node->right, key, metrics, metricsId);
}

template <typename TKey, typename TValue>
void RedBlackTree<TKey, TValue>::fixInsert(Node<TKey, TValue> *k)
{
  Node<TKey, TValue> *u;
  while (k->parent->color == RED)
  {
    if (k->parent == k->parent->parent->right)
    {
      u = k->parent->parent->left; // tio
      if (u->color == RED)
      {
        u->color = BLACK;
        k->parent->color = BLACK;
        k->parent->parent->color = RED;
        k = k->parent->parent;
      }
      else
      {
        if (k == k->parent->left)
        {
          k = k->parent;
          rightRotate(k);
        }
        k->parent->color = BLACK;
        k->parent->parent->color = RED;
        leftRotate(k->parent->parent);
      }
    }
    else
    {
      u = k->parent->parent->right; // tio
      if (u->color == RED)
      {
        u->color = BLACK;
        k->parent->color = BLACK;
        k->parent->parent->color = RED;
        k = k->parent->parent;
      }
      else
      {
        if (k == k->parent->right)
        {
          k = k->parent;
          leftRotate(k);
        }
        k->parent->color = BLACK;
        k->parent->parent->color = RED;
        rightRotate(k->parent->parent);
      }
    }
    if (k == root)
    {
      break;
    }
  }
  root->color = BLACK;
}

template <typename TKey, typename TValue>
void RedBlackTree<TKey, TValue>::leftRotate(Node<TKey, TValue> *x)
{
  Node<TKey, TValue> *y = x->right;
  x->right = y->left;
  if (y->left != TNULL)
  {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr)
  {
    this->root = y;
  }
  else if (x == x->parent->left)
  {
    x->parent->left = y;
  }
  else
  {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

template <typename TKey, typename TValue>
void RedBlackTree<TKey, TValue>::rightRotate(Node<TKey, TValue> *x)
{
  Node<TKey, TValue> *y = x->left;
  x->left = y->right;
  if (y->right != TNULL)
  {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr)
  {
    this->root = y;
  }
  else if (x == x->parent->right)
  {
    x->parent->right = y;
  }
  else
  {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

template <typename TKey, typename TValue>
RedBlackTree<TKey, TValue>::RedBlackTree()
{
  TNULL = new Node<TKey, TValue>(TKey(), TValue());
  TNULL->color = BLACK;
  root = TNULL;
}

template <typename TKey, typename TValue>
void RedBlackTree<TKey, TValue>::insert(TKey key, TValue fileLocation, Metrics *metrics, int metricsId)
{
  Node<TKey, TValue> *node = new Node<TKey, TValue>(key, fileLocation);
  node->parent = nullptr;
  node->left = TNULL;
  node->right = TNULL;
  node->color = RED;

  Node<TKey, TValue> *y = nullptr;
  Node<TKey, TValue> *x = this->root;

  while (x != TNULL)
  {
    y = x;
    if (metrics != nullptr)
    {
      metrics->addComparisons(metricsId); // Contabiliza uma comparação
    }
    if (node->id < x->id)
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }

  node->parent = y;
  if (y == nullptr)
  {
    root = node;
  }
  else if (node->id < y->id)
  {
    y->left = node;
  }
  else
  {
    y->right = node;
  }

  if (node->parent == nullptr)
  {
    node->color = BLACK;
    return;
  }

  if (node->parent->parent == nullptr)
  {
    return;
  }

  fixInsert(node);
}

template <typename TKey, typename TValue>
bool RedBlackTree<TKey, TValue>::search(TKey key, Metrics *metrics, int metricsId)
{
  Node<TKey, TValue> *result = searchTreeHelper(this->root, key, metrics, metricsId);
  return (result != TNULL);
}

template <typename TKey, typename TValue>
void RedBlackTree<TKey, TValue>::printTree()
{
  preOrderHelper(this->root);
}

template <typename TKey, typename TValue>
RedBlackTree<TKey, TValue>::~RedBlackTree() {
    deleteSubTree(root);  // Chama a função recursiva para desalocar memória
    delete TNULL;  // Também é necessário desalocar o nó NULL
}

template <typename TKey, typename TValue>
void RedBlackTree<TKey, TValue>::deleteSubTree(Node<TKey, TValue> *node) {
    if (node != TNULL) {
        deleteSubTree(node->left);  // Desaloca a subárvore esquerda
        deleteSubTree(node->right); // Desaloca a subárvore direita
        delete node;  // Desaloca o próprio nó
    }
}
