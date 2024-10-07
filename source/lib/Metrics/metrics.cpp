#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "metrics.h"

int Metrics::currentId = 0;

Metrics::Metrics()
{
  this->currentId = 0;
}

int Metrics::createBlock(std::string label)
{
  metricsBlock newBlock;
  newBlock.id = currentId;
  newBlock.label = label;
  newBlock.comparisons = 0;
  newBlock.movements = 0;
  newBlock.duration = 0.0;
  this->currentId++;

  this->blocks.push_back(newBlock);

  return newBlock.id;
}

void Metrics::addComparisons(int blockId)
{
  for (auto &block : blocks)
  {
    if (block.id == blockId)
    {
      block.comparisons++;
      return;
    }
  }
}

void Metrics::addMovements(int blockId)
{
  for (auto &block : blocks)
  {
    if (block.id == blockId)
    {
      block.movements++;
      return;
    }
  }
}

void Metrics::startTimer(int blockId)
{
  for (auto &block : blocks)
  {
    if (block.id == blockId)
    {
      block.startTime = std::chrono::steady_clock::now(); // Usando steady_clock
      return;
    }
  }
}

void Metrics::stopTimer(int blockId)
{
  for (auto &block : blocks)
  {
    if (block.id == blockId)
    {
      auto endTime = std::chrono::steady_clock::now(); // Usando steady_clock
      std::chrono::duration<double> diff = endTime - block.startTime;
      block.duration = diff.count();
      return;
    }
  }
}

Metrics::metricsBlock Metrics::getMetricsByBlockId(int blockId)
{
  for (const auto &block : blocks)
  {
    if (block.id == blockId)
    {
      return block;
    }
  }
  throw std::invalid_argument("Bloco com o ID fornecido não encontrado.");
}

void Metrics::printResults()
{
  std::cout << "Resultados das métricas:\n";
  std::cout << std::setprecision(9) << std::fixed;
  for (const auto &block : blocks)
  {
    std::cout << "Bloco: " << block.label << " (ID: " << block.id << "):\n";
    std::cout << "Comparações: " << block.comparisons << "\n";
    std::cout << "Movimentações: " << block.movements << "\n";
    std::cout << "Duração: " << block.duration << " segundos\n";
  }
}

std::string Metrics::getFormattedResults()
{
  std::ostringstream outFile;
  outFile << "Resultados das métricas:\n\n";
  std::cout << std::setprecision(9) << std::fixed;
  int i = 0;
  for (const auto &block : blocks)
  {
    outFile << "Bloco " << block.label << " (ID: " << block.id << "):\n";
    outFile << "Comparações: " << block.comparisons << "\n";
    outFile << "Movimentações: " << block.movements << "\n";
    outFile << "Duração: " << block.duration << " segundos\n";
    if (i != blocks.size() - 1)
    {
      outFile << "--------------------------------\n";
    }
    i++;
  }
  return outFile.str();
}
