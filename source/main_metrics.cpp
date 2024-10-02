#include <iostream>
#include "metrics.h"
#include <chrono>
#include <thread>

int main()
{
  Metrics testMetrics;

  auto id = testMetrics.createBlock("Bloco 1");

  testMetrics.addComparisons(id);
  testMetrics.addComparisons(id);
  testMetrics.addComparisons(id);

  testMetrics.startTimer(id);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  testMetrics.stopTimer(id);

  testMetrics.printResults();

  std::cout << "Nome do filme: " << std::endl;
  std::cout << std::endl;

  return 0;
}
