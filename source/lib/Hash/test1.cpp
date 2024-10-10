#include <iostream>
#include <string>
#include "hash.h"
#include <cassert>

// Testa Hash
int main()
{
  HashTable hashTable(5);

  hashTable.insert("a");
  hashTable.insert("a");
  hashTable.insert("a");

  auto entries = hashTable.getAllEntries();

  assert(entries[0].first == "a");
  assert(entries[0].second == 3);

  return 0;
}
