#include <iostream>
#include <string>
#include <cassert>
#include "metrics.h"

// Testa Metrics - comparações e movimentações
int main()
{
  Metrics testMetrics;

  auto id1 = testMetrics.createBlock("Bloco 1");
  auto id2 = testMetrics.createBlock("Bloco 2");
  auto id3 = testMetrics.createBlock("Bloco não usado");

  testMetrics.addComparisons(id1);
  testMetrics.addMovements(id1);

  testMetrics.addComparisons(id2);
  testMetrics.addMovements(id2);
  testMetrics.addMovements(id2);
  testMetrics.addMovements(id2);

  testMetrics.addComparisons(id3);
  testMetrics.addMovements(id3);

  std::vector<int> firstAndSecondIds = {id1, id2};

  Metrics::metricsBlock averageMetrics = testMetrics.calculateAverageMetrics(firstAndSecondIds);

  assert(averageMetrics.comparisons == 1);
  assert(averageMetrics.movements == 2);
  return 0;
}
