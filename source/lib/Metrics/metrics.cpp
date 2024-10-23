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

Metrics::metricsBlock Metrics::calculateAverageMetrics(const std::vector<int> &ids)
{
  metricsBlock averageMetrics;
  int totalComparisons = 0;
  int totalMovements = 0;
  double totalDuration = 0.0;
  int count = 0;

  for (const int id : ids)
  {
    if (id >= 0 && id < blocks.size())
    {
      totalComparisons += blocks[id].comparisons;
      totalMovements += blocks[id].movements;
      totalDuration += blocks[id].duration;
      count++;
    }
  }

  if (count > 0)
  {
    averageMetrics.comparisons = totalComparisons / count;
    averageMetrics.movements = totalMovements / count;
    averageMetrics.duration = totalDuration / count;
  }
  else
  {
    averageMetrics.comparisons = 0;
    averageMetrics.movements = 0;
    averageMetrics.duration = 0.0;
  }

  return averageMetrics;
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
