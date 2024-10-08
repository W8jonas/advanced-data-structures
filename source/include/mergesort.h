#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include <chrono>
#include "metrics.h"

template <typename T>
class Mergesort
{
public:
    static void mergesort(std::vector<T> &items, Metrics *metrics = nullptr, int metricsId = -1);

private:
    static void mergesortHelper(std::vector<T> &items, int left, int right, Metrics *metrics, int metricsId);
    static void merge(std::vector<T> &items, int left, int mid, int right, Metrics *metrics, int metricsId);
};

#include "mergesort.tpp"

#endif // MERGESORT_H
