#include <chrono>
#include <iostream>
#include <type_traits>
#include "heapsort.h"
#include "film.h"

template <typename T>
void Heapsort<T>::heapify(std::vector<T> &films, int n, int i, Metrics *metrics, int metricsId)
{
    int largest = i;       // Inicializa o maior como raiz
    int left = 2 * i + 1;  // Filho esquerdo
    int right = 2 * i + 2; // Filho direito

    if constexpr (std::is_same<T, Film>::value)
    {
        if (left < n && films[left].popularity <= films[largest].popularity)
        {
            largest = left;
        }

        if (right < n && films[right].popularity <= films[largest].popularity)
        {
            largest = right;
        }
    }
    else
    {
        if (left < n && films[left] <= films[largest])
        {
            largest = left;
        }

        if (right < n && films[right] <= films[largest])
        {
            largest = right;
        }
    }

    if (largest != i)
    {
        std::swap(films[i], films[largest]); // Troca
        if (metrics != nullptr)
        {
            metrics->addMovements(metricsId);   // Contabiliza uma movimentações
            metrics->addComparisons(metricsId); // Contabiliza uma comparação
        }
        heapify(films, n, largest, metrics, metricsId); // Recursão para heapify a subárvore afetada
    }
}

template <typename T>
void Heapsort<T>::heapsort(std::vector<T> &films, Metrics *metrics, int metricsId)
{
    if (metrics != nullptr)
    {
        metrics->startTimer(metricsId); // Marca o início da execução
    }

    int n = films.size();

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(films, n, i, metrics, metricsId);
    }

    for (int i = n - 1; i > 0; i--)
    {
        std::swap(films[0], films[i]); // Troca a raiz com o último elemento
        if (metrics != nullptr)
        {
            metrics->addMovements(metricsId); // Contabiliza uma movimentações
        }
        heapify(films, i, 0, metrics, metricsId); // Chama heapify na raiz
    }

    if (metrics != nullptr)
    {
        metrics->stopTimer(metricsId); // Marca o fim da execução
    }
}
