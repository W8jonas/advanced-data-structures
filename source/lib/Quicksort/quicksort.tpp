#include "quicksort.h"
#include "film.h"

// Implementação do algoritmo Quicksort
template <typename T>
void Quicksort<T>::quicksortHelper(std::vector<T> &films, int low, int high, Metrics *metrics, int metricsId)
{
    if (low < high)
    {                          // Verifica se ainda há elementos para ordenar
        T pivot = films[high]; // Escolhe o último elemento como pivô
        int i = (low - 1);     // Índice do menor element'o

        // Loop para comparar e organizar os elementos em relação ao pivô
        for (int j = low; j <= high - 1; j++)
        {
            if (metrics != nullptr)
            {
                metrics->addComparisons(metricsId); // Contabiliza uma comparação
            }
            if constexpr (std::is_same<T, Film>::value)
            {
                if (films[j].popularity >= pivot.popularity)
                {                                  // Se o elemento atual for menor que o pivô
                    i++;                           // Incrementa o índice do menor elemento
                    std::swap(films[i], films[j]); // Troca os elementos
                    if (metrics != nullptr)
                    {
                        metrics->addMovements(metricsId); // Contabiliza uma movimentações
                    }
                }
            }
            else
            {
                if (films[j] >= pivot)
                {                                  // Se o elemento atual for menor que o pivô
                    i++;                           // Incrementa o índice do menor elemento
                    std::swap(films[i], films[j]); // Troca os elementos
                    if (metrics != nullptr)
                    {
                        metrics->addMovements(metricsId); // Contabiliza uma movimentações
                    }
                }
            }
        }
        std::swap(films[i + 1], films[high]); // Coloca o pivô na posição correta
        if (metrics != nullptr)
        {
            metrics->addMovements(metricsId); // Contabiliza uma movimentações
        }
        int pi = i + 1; // Índice do pivô

        // Chama recursivamente para as duas metades
        quicksortHelper(films, low, pi - 1, metrics, metricsId);
        quicksortHelper(films, pi + 1, high, metrics, metricsId);
    }
}

// Função principal do Quicksort que inicializa o resultado e mede o tempo de execução
template <typename T>
void Quicksort<T>::quicksort(std::vector<T> &films, Metrics *metrics, int metricsId)
{
    if (metrics != nullptr)
    {
        metrics->startTimer(metricsId); // Marca o início da execução
    }
    quicksortHelper(films, 0, films.size() - 1, metrics, metricsId); // Chama a função auxiliar
    if (metrics != nullptr)
    {
        metrics->stopTimer(metricsId); // Marca o fim da execução
    }
}
