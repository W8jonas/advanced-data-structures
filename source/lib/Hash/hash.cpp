#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "hash.h"

// Construtor: inicializa a tabela hash com o tamanho especificado
HashTable::HashTable(size_t size)
{
  tableSize = size;   // Inicializa o tamanho da tabela
  table.resize(size); // Redimensiona o vetor para o tamanho especificado
}

// Função para inserir um valor de voteAverage na tabela hash
void HashTable::insert(const std::string &voteAverage)
{
  size_t index = hashFunction(voteAverage);
  // std::cout << "hashFunction " << voteAverage << " " << index << std::endl;

  for (auto &pair : table[index])
  {
    if (pair.first == voteAverage)
    {
      pair.second++; // Incrementa a contagem
      return;
    }
  }
  // Se não encontrar o voteAverage, insere uma nova entrada
  table[index].emplace_back(voteAverage, 1);
}

// Função para retornar todas as entradas da tabela hash
std::vector<std::pair<std::string, int>> HashTable::getAllEntries()
{
  std::vector<std::pair<std::string, int>> entries;
  for (auto &bucket : table)
  {
    for (auto &pair : bucket)
    {
      // std::cout << "getAllEntries " << pair.first << " " << pair.second << std::endl;
      entries.push_back(pair);
    }
  }
  return entries;
}

// Função hash que mapeia voteAverage para um índice da tabela
size_t HashTable::hashFunction(const std::string &voteAverage) const
{
  size_t hash = 0;
  for (char c : voteAverage)
  {
    // Multiplica por um número primo (31) cada letra e acumula
    hash = hash * 31 + c;
  }

  return hash % tableSize;
}
