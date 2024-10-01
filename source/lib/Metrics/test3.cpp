#include <iostream>
#include <string>
#include <cassert>
#include "metrics.h"
#include <chrono>
#include <thread>

// Testa Metrics - comparações, movimentações e timer em diferentes blocos
int main()
{
  Metrics testMetrics;

  auto id1 = testMetrics.createBlock("Bloco 1");
  auto id2 = testMetrics.createBlock("Bloco 2");

  testMetrics.addComparisons(id1);
  testMetrics.addMovements(id1);

  testMetrics.addComparisons(id2);
  testMetrics.addMovements(id2);

  testMetrics.addComparisons(id1);
  testMetrics.addMovements(id2);

  testMetrics.startTimer(id1);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  testMetrics.stopTimer(id1);

  Metrics::metricsBlock metricsBlock1 = testMetrics.getMetricsByBlockId(id1);
  assert(metricsBlock1.comparisons == 2);
  assert(metricsBlock1.movements == 1);
  assert(metricsBlock1.duration > 0.5 && metricsBlock1.duration < 0.510); // 10ms de tolerância

  Metrics::metricsBlock metricsBlock2 = testMetrics.getMetricsByBlockId(id2);
  assert(metricsBlock2.comparisons == 1);
  assert(metricsBlock2.movements == 2);

  return 0;
}
