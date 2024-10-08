#include "mergesort.h"
#include "film.h"
#include <type_traits>

// Implementação do algoritmo Merge Sort
template <typename T>
void Mergesort<T>::merge(std::vector<T> &items, int left, int mid, int right, Metrics *metrics, int metricsId)
{
    int n1 = mid - left + 1; // Tamanho do subarray esquerdo
    int n2 = right - mid;    // Tamanho do subarray direito

    std::vector<T> leftArray(n1);
    std::vector<T> rightArray(n2);

    // Copia os dados para os subarrays
    for (int i = 0; i < n1; i++)
        leftArray[i] = items[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = items[mid + 1 + j];

    // Índices iniciais do subarray
    int i = 0, j = 0;
    int k = left;

    // Mescla os subarrays de volta em items[left..right]
    while (i < n1 && j < n2)
    {
        if (metrics != nullptr)
        {
            metrics->addComparisons(metricsId); // Contabiliza uma comparação, se o metrics não for nullptr
        }
        if constexpr (std::is_same<T, Film>::value)
        {
            if (leftArray[i].popularity >= rightArray[j].popularity)
            {
                items[k] = leftArray[i];
                i++;
            }
            else
            {
                items[k] = rightArray[j];
                j++;
            }
        }
        else
        {
            if (leftArray[i] >= rightArray[j])
            {
                items[k] = leftArray[i];
                i++;
            }
            else
            {
                items[k] = rightArray[j];
                j++;
            }
        }

        if (metrics != nullptr)
        {
            metrics->addMovements(metricsId); // Contabiliza uma movimentação
        }
        k++;
    }

    // Copia os elementos restantes de leftArray, se houver
    while (i < n1)
    {
        items[k] = leftArray[i];
        i++;
        k++;
        if (metrics != nullptr)
        {
            metrics->addMovements(metricsId); // Contabiliza uma movimentação
        }
    }

    // Copia os elementos restantes de rightArray, se houver
    while (j < n2)
    {
        items[k] = rightArray[j];
        j++;
        k++;
        if (metrics != nullptr)
        {
            metrics->addMovements(metricsId); // Contabiliza uma movimentação
        }
    }
}

template <typename T>
void Mergesort<T>::mergesortHelper(std::vector<T> &items, int left, int right, Metrics *metrics, int metricsId)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // Chama recursivamente para as duas metades
        mergesortHelper(items, left, mid, metrics, metricsId);
        mergesortHelper(items, mid + 1, right, metrics, metricsId);

        merge(items, left, mid, right, metrics, metricsId); // Mescla as metades
    }
}

// Função principal do Merge Sort que inicializa o resultado e mede o tempo de execução
template <typename T>
void Mergesort<T>::mergesort(std::vector<T> &items, Metrics *metrics, int metricsId)
{
    if (metrics != nullptr)
    {
        metrics->startTimer(metricsId); // Marca o início da execução
    }
    mergesortHelper(items, 0, items.size() - 1, metrics, metricsId); // Chama a função auxiliar
    if (metrics != nullptr)
    {
        metrics->stopTimer(metricsId); // Marca o fim da execução
    }
}
