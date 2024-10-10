
template <typename TKey, typename TValue>
BTreeNode<TKey, TValue>::BTreeNode(int t, bool leaf)
{
  this->t = t;
  this->leaf = leaf;

  keys = new TKey[2 * t - 1];
  values = new TValue[2 * t - 1];
  children = new BTreeNode *[2 * t];

  n = 0;
}

template <typename TKey, typename TValue>
void BTreeNode<TKey, TValue>::insertNonFull(TKey key, TValue value)
{
  int i = n - 1;

  if (leaf)
  {
    while (i >= 0 && keys[i] > key)
    {
      keys[i + 1] = keys[i];
      values[i + 1] = values[i];
      i--;
    }

    keys[i + 1] = key;
    values[i + 1] = value;
    n = n + 1;
  }
  else
  {
    while (i >= 0 && keys[i] > key)
    {
      i--;
    }

    if (children[i + 1]->n == 2 * t - 1)
    {
      splitChild(i + 1, children[i + 1]);

      if (keys[i + 1] < key)
      {
        i++;
      }
    }
    children[i + 1]->insertNonFull(key, value);
  }
}

template <typename TKey, typename TValue>
void BTreeNode<TKey, TValue>::splitChild(int i, BTreeNode<TKey, TValue> *y)
{
  BTreeNode<TKey, TValue> *z = new BTreeNode(y->t, y->leaf);
  z->n = t - 1;

  for (int j = 0; j < t - 1; j++)
  {
    z->keys[j] = y->keys[j + t];
    z->values[j] = y->values[j + t];
  }

  if (!y->leaf)
  {
    for (int j = 0; j < t; j++)
    {
      z->children[j] = y->children[j + t];
    }
  }

  y->n = t - 1;

  for (int j = n; j >= i + 1; j--)
  {
    children[j + 1] = children[j];
  }

  children[i + 1] = z;

  for (int j = n - 1; j >= i; j--)
  {
    keys[j + 1] = keys[j];
    values[j + 1] = values[j];
  }

  keys[i] = y->keys[t - 1];
  values[i] = y->values[t - 1];

  n = n + 1;
}

template <typename TKey, typename TValue>
BTreeNode<TKey, TValue> *BTreeNode<TKey, TValue>::search(TKey key, Metrics *metrics, int metricsId)
{
  int i = 0;
  while (i < n && key > keys[i])
  {
    i++;
    if (metrics != nullptr)
    {
      metrics->addComparisons(metricsId); // Contabiliza uma comparação
    }
  }

  if (keys[i] == key)
  {
    if (metrics != nullptr)
    {
      metrics->addComparisons(metricsId); // Contabiliza uma comparação
    }
    return this;
  }

  if (leaf)
  {
    return nullptr;
  }

  return children[i]->search(key, metrics, metricsId);
}

template <typename TKey, typename TValue>
void BTreeNode<TKey, TValue>::traverse()
{
  int i;
  for (i = 0; i < n; i++)
  {
    if (!leaf)
    {
      children[i]->traverse();
    }
    std::cout << keys[i] << " ";
  }

  if (!leaf)
  {
    children[i]->traverse();
  }
}

template <typename TKey, typename TValue>
BTree<TKey, TValue>::BTree(int t)
{
  root = nullptr;
  this->t = t;
}

template <typename TKey, typename TValue>
void BTree<TKey, TValue>::insert(TKey key, TValue value, Metrics *metrics, int metricsId)
{
  if (root == nullptr)
  {
    root = new BTreeNode<TKey, TValue>(t, true);
    root->keys[0] = key;
    root->values[0] = value;
    root->n = 1;
  }
  else
  {
    if (root->n == 2 * t - 1)
    {
      BTreeNode<TKey, TValue> *s = new BTreeNode<TKey, TValue>(t, false);
      s->children[0] = root;

      s->splitChild(0, root);

      int i = 0;
      if (s->keys[0] < key)
      {
        i++;
      }
      s->children[i]->insertNonFull(key, value);

      root = s;
    }
    else
    {
      root->insertNonFull(key, value);
    }
  }
}

template <typename TKey, typename TValue>
bool BTree<TKey, TValue>::search(TKey key, Metrics *metrics, int metricsId)
{
  if (root == nullptr)
  {
    return false;
  }
  else
  {
    return (root->search(key, metrics, metricsId) != nullptr);
  }
}

template <typename TKey, typename TValue>
void BTree<TKey, TValue>::traverse()
{
  if (root != nullptr)
  {
    root->traverse();
  }
}

template <typename TKey, typename TValue>
BTreeNode<TKey, TValue>::~BTreeNode() {
    if (!leaf) {
        for (int i = 0; i <= n; i++) {
            delete children[i];  // Desaloca os filhos recursivamente
        }
    }
    delete[] keys;  // Desaloca as chaves
    delete[] values;  // Desaloca os valores
}

template <typename TKey, typename TValue>
BTree<TKey, TValue>::~BTree() {
    deleteSubTree(root);  // Chama a função recursiva para desalocar memória
}

template <typename TKey, typename TValue>
void BTree<TKey, TValue>::deleteSubTree(BTreeNode<TKey, TValue> *node) {
    if (node != nullptr) {
        delete node;  // Desaloca o nó recursivamente
    }
}
