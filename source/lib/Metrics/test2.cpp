#include <iostream>
#include <string>
#include <cassert>
#include "metrics.h"

// Testa Metrics - comparações e movimentações
int main()
{
  Metrics testMetrics;

  auto id = testMetrics.createBlock("Bloco 1");

  testMetrics.addComparisons(id);
  testMetrics.addMovements(id);

  testMetrics.addComparisons(id);
  testMetrics.addMovements(id);

  testMetrics.addComparisons(id);
  testMetrics.addMovements(id);

  Metrics::metricsBlock metricsBlock = testMetrics.getMetricsByBlockId(id);
  assert(metricsBlock.comparisons == 3);
  assert(metricsBlock.movements == 3);
  return 0;
}
