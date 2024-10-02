#include "mergesort.h"

// Implementação do algoritmo Merge Sort
void Mergesort::merge(std::vector<Film> &films, int left, int mid, int right, SortResult &result) {
    int n1 = mid - left + 1; // Tamanho do subarray esquerdo
    int n2 = right - mid;    // Tamanho do subarray direito

    std::vector<Film> leftArray(n1);
    std::vector<Film> rightArray(n2);

    // Copia os dados para os subarrays
    for (int i = 0; i < n1; i++)
        leftArray[i] = films[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = films[mid + 1 + j];

    // Índices iniciais do subarray
    int i = 0, j = 0;
    int k = left;

    // Mescla os subarrays de volta em films[left..right]
    while (i < n1 && j < n2) {
        result.comparisons++; // Contabiliza uma comparação
        if (leftArray[i].popularity <= rightArray[j].popularity) {
            films[k] = leftArray[i];
            i++;
        } else {
            films[k] = rightArray[j];
            j++;
        }
        result.movements++; // Contabiliza uma movimentação
        k++;
    }

    // Copia os elementos restantes de leftArray, se houver
    while (i < n1) {
        films[k] = leftArray[i];
        i++;
        k++;
        result.movements++; // Contabiliza uma movimentação
    }

    // Copia os elementos restantes de rightArray, se houver
    while (j < n2) {
        films[k] = rightArray[j];
        j++;
        k++;
        result.movements++; // Contabiliza uma movimentação
    }
}

void Mergesort::mergesortHelper(std::vector<Film> &films, int left, int right, SortResult &result) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Chama recursivamente para as duas metades
        mergesortHelper(films, left, mid, result);
        mergesortHelper(films, mid + 1, right, result);
        
        merge(films, left, mid, right, result); // Mescla as metades
    }
}

// Função principal do Merge Sort que inicializa o resultado e mede o tempo de execução
Mergesort::SortResult Mergesort::mergesort(std::vector<Film> &films) {
    SortResult result = {0, 0, 0}; // Inicializa as métricas de desempenho
    auto start = std::chrono::high_resolution_clock::now(); // Marca o início da execução
    
    mergesortHelper(films, 0, films.size() - 1, result); // Chama a função auxiliar

    auto end = std::chrono::high_resolution_clock::now(); // Marca o fim da execução
    result.duration = std::chrono::duration<double>(end - start).count(); // Calcula a duração
    return result; // Retorna os resultados da ordenação
}