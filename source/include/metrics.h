#ifndef METRICS_H
#define METRICS_H

#include <string>
#include <vector>
#include <chrono>

class Metrics
{
public:
  struct metricsBlock
  {
    int id;
    std::string label;
    int comparisons;
    int movements;
    std::chrono::steady_clock::time_point startTime;  // Corrigido o namespace
    double duration;
  };
  
  Metrics();
  int createBlock(std::string label);
  void addComparisons(int blockId);
  void addMovements(int blockId);
  void startTimer(int blockId);
  void stopTimer(int blockId);
  void printResults();
  void writeFileResults();
  metricsBlock getMetricsByBlockId(int blockId);

private:
  std::vector<metricsBlock> blocks;
  static int currentId;
};

#endif
