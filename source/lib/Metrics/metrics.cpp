#include <iostream>
#include <vector>
#include <fstream>
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
}

void Metrics::stopTimer(int blockId)
{
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
}

void Metrics::writeFileResults()
{
}
