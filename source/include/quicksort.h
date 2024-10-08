#ifndef SORT_H
#define SORT_H

#include <vector>
#include <chrono>
#include "metrics.h"

template <typename T>
class Quicksort
{
public:
    static void quicksort(std::vector<T> &films, Metrics *metrics = nullptr, int metricsId = -1);

private:
    static void quicksortHelper(std::vector<T> &films, int low, int high, Metrics *metrics, int metricsId);
};

#include "quicksort.tpp"
#endif // SORT_H
