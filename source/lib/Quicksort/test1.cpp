#include <iostream>
#include <vector>
#include <cassert>
#include "quicksort.h"
#include "fileManager.h"
#include "film.h"
#include "metrics.h"

int main()
{
  std::vector<int> numbers = {5, 3, 1, 4, 2};
  Quicksort<int>::quicksort(numbers);
  assert(numbers[0] == 5);
  assert(numbers[1] == 4);
  assert(numbers[2] == 3);
  assert(numbers[3] == 2);
  assert(numbers[4] == 1);
  return 0;
}
