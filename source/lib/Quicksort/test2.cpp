#include <iostream>
#include <vector>
#include "quicksort.h"
#include "fileManager.h" 

// Função para testar o desempenho do Quicksort com filmes reais
void testQuickSortPerformance() {
    // Caminhos para os arquivos CSV e binário
    std::string entryPath = "../source/data/";
    std::string csvFilename = "movies_dataset_min.csv";
    std::string binaryFilename = "filmes.bin";

    // Cria uma instância de fileManager para gerenciar os arquivos CSV e binário
    fileManager fm(entryPath);
    fm.convertCSV2Bin(csvFilename, binaryFilename);
    
    // Vetor para armazenar todos os filmes carregados do arquivo binário
    std::vector<Film> films;
    fm.getAllFilms(films); // Carrega todos os filmes do arquivo binário

    // Verifica se há filmes carregados
    if (films.empty()) {
        std::cerr << "Nenhum filme foi carregado!" << std::endl;
        return;
    }

    // Aplica o algoritmo de Quicksort nos filmes
    Quicksort::SortResult result = Quicksort::quicksort(films);

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
