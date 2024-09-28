#include "quicksort.h"

// Implementação do algoritmo Quicksort
void Sort::quicksortHelper(std::vector<Film> &films, int low, int high, SortResult &result) {
    if (low < high) { // Verifica se ainda há elementos para ordenar
        Film pivot = films[high]; // Escolhe o último elemento como pivô
        int i = (low - 1); // Índice do menor element'o

        // Loop para comparar e organizar os elementos em relação ao pivô
        for (int j = low; j <= high - 1; j++) {
            result.comparisons++; // Contabiliza uma comparação
            if (films[j].popularity < pivot.popularity) { // Se o elemento atual for menor que o pivô
                i++; // Incrementa o índice do menor elemento
                std::swap(films[i], films[j]); // Troca os elementos
                result.movements += 2; // Contabiliza duas movimentações (swap)
            }
        }
        std::swap(films[i + 1], films[high]); // Coloca o pivô na posição correta
        result.movements++; // Contabiliza uma movimentação para a troca do pivô
        int pi = i + 1; // Índice do pivô

        // Chama recursivamente para as duas metades
        quicksortHelper(films, low, pi - 1, result);
        quicksortHelper(films, pi + 1, high, result);
    }
}

// Função principal do Quicksort que inicializa o resultado e mede o tempo de execução
Sort::SortResult Sort::quicksort(std::vector<Film> &films) {
    SortResult result = {0, 0, 0}; // Inicializa as métricas de desempenho
    auto start = std::chrono::high_resolution_clock::now(); // Marca o início da execução
    
    quicksortHelper(films, 0, films.size() - 1, result); // Chama a função auxiliar

    auto end = std::chrono::high_resolution_clock::now(); // Marca o fim da execução
    result.duration = std::chrono::duration<double>(end - start).count(); // Calcula a duração
    return result; // Retorna os resultados da ordenação
}
