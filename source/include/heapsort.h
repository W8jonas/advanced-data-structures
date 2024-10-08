#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include "metrics.h"

template <typename T>
class Heapsort
{
public:
    static void heapsort(std::vector<T> &films, Metrics *metrics = nullptr, int metricsId = -1);

private:
    static void heapify(std::vector<T> &films, int n, int i, Metrics *metrics, int metricsId);
};

#include "heapsort.tpp"

#endif // HEAPSORT_H
