#include <iostream>
#include <vector>
#include <cassert>
#include "quicksort.h"
#include "fileManager.h" 

// Função para testar a ordenação do Quicksort com filmes reais
void testQuickSortFilms() { // Nome da função alterado
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
    assert(!films.empty() && "Nenhum filme foi carregado!");

    // Aplica o algoritmo de Quicksort nos filmes
    Quicksort::SortResult result = Quicksort::quicksort(films);

    // Verifica se os filmes estão ordenados pela popularidade
    for (size_t i = 1; i < films.size(); ++i) {
        assert(films[i - 1].popularity >= films[i].popularity && "Os filmes não estão ordenados corretamente!");
    }

    std::cout << "Teste de ordenação com filmes reais passou!" << std::endl;
}

// Função principal para executar os testes
int main() {
    // Testa a ordenação do Quicksort com filmes reais
    testQuickSortFilms(); // Chamada da função com o novo nome

    return 0;
}
