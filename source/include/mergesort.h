#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include <chrono>
#include "film.h" // Include Film structure

class Mergesort {
public:
    struct SortResult {
        int comparisons; // Number of comparisons made
        int movements;   // Number of movements made (swaps)
        double duration; // Duration of the sorting process in seconds
    };

    static SortResult mergesort(std::vector<Film> &films);

private:
    static void mergesortHelper(std::vector<Film> &films, int left, int right, SortResult &result);
    static void merge(std::vector<Film> &films, int left, int mid, int right, SortResult &result);
};

#endif // MERGESORT_H