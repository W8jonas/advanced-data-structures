#include <iostream>
#include <vector>
#include "quicksort.h"
#include "fileManager.h" 

// Função para testar o desempenho do Quicksort com filmes reais
void testQuickSortPerformance() {
    // Caminhos para os arquivos CSV e binário
    std::string csvPath = "../source/data/movies_dataset_min.csv";
    std::string binaryPath = "../source/data/filmes.bin";

    // Cria uma instância de fileManager para gerenciar os arquivos CSV e binário
    fileManager fm(csvPath, binaryPath);
    
    // Vetor para armazenar todos os filmes carregados do arquivo binário
    std::vector<Film> films;
    fm.getAllFilms(films); // Carrega todos os filmes do arquivo binário

    // Verifica se há filmes carregados
    if (films.empty()) {
        std::cerr << "Nenhum filme foi carregado!" << std::endl;
        return;
    }

    // Aplica o algoritmo de Quicksort nos filmes
    Sort::SortResult result = Sort::quicksort(films);

    // Exibe as métricas de desempenho
    std::cout << "Teste de desempenho com filmes reais:" << std::endl;
    std::cout << "Comparações: " << result.comparisons << std::endl;
    std::cout << "Movimentações: " << result.movements << std::endl;
    std::cout << "Duração: " << result.duration << " segundos" << std::endl;
}

// Função principal para executar os testes
int main() {
    // Testa o desempenho do Quicksort com filmes reais
    testQuickSortPerformance();

    return 0;
}
