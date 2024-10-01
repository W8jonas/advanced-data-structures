#ifndef SORT_H
#define SORT_H

#include <vector>
#include <chrono>
#include "film.h" // Include Film structure

class Quicksort
{
public:
    struct SortResult
    {
        int comparisons; // Number of comparisons made
        int movements;   // Number of movements made (swaps)
        double duration; // Duration of the sorting process in seconds
    };

    static SortResult quicksort(std::vector<Film> &films);
    static SortResult heapsort(std::vector<Film> &films);
    static SortResult mergesort(std::vector<Film> &films);

private:
    static void quicksortHelper(std::vector<Film> &films, int low, int high, SortResult &result);
    static void heapify(std::vector<Film> &films, int n, int i, SortResult &result);
    static void mergesortHelper(std::vector<Film> &films, int left, int right, SortResult &result);
    static void merge(std::vector<Film> &films, int left, int mid, int right, SortResult &result);
};

#endif // SORT_H
