#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <utility> // Para std::pair
#include <string>
class HashTable
{
public:
  HashTable(size_t size);
  void insert(const std::string &voteAverage);
  std::vector<std::pair<std::string, int>> getAllEntries();

private:
  std::vector<std::list<std::pair<std::string, int>>> table;
  size_t tableSize;
  size_t hashFunction(const std::string &voteAverage) const;
};

#endif // HASHTABLE_H
