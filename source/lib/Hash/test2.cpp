#include <iostream>
#include <string>
#include "hash.h"
#include <cassert>

// Testa Hash
int main()
{
  HashTable hashTable(3);

  hashTable.insert("a"); // 61 [a in ASCII] * 31 => 1.891 % 3 => 1

  hashTable.insert("b"); // 62 [b in ASCII] * 31 => 1.922 % 3 => 2
  hashTable.insert("b");

  hashTable.insert("c"); // 63 [c in ASCII] * 31 => 1.953 % 3 => 0
  hashTable.insert("c");
  hashTable.insert("c");

  auto entries = hashTable.getAllEntries();

  assert(entries[0].first == "c" && entries[0].second == 3);
  assert(entries[1].first == "a" && entries[1].second == 1);
  assert(entries[2].first == "b" && entries[2].second == 2);

  return 0;
}
