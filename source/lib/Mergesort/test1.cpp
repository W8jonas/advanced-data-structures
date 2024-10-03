#include <iostream>
#include <vector>
#include "mergesort.h"
#include "fileManager.h" // Inclua o cabeçalho que contém a definição da classe fileManager

void runMergeSortTest(int n) {
    // Caminhos para os arquivos CSV e binário
    std::string entryPath = "../source/data/";
    std::string csvFilename = "movies_dataset_min.csv";
    std::string binaryFilename = "filmes.bin";

    // Cria uma instância de fileManager para gerenciar os arquivos CSV e binário
    fileManager fm(entryPath);
    fm.convertCSV2Bin(csvFilename, binaryFilename);

    std::vector<Film> films;

    // Obtém todos os filmes do arquivo binário
    fm.getAllFilms(films);

    // Se N for maior que o número de filmes disponíveis, ajuste N
    if (n > films.size()) {
        n = films.size();
    }

    // Seleciona N filmes aleatórios
    std::vector<Film> selectedFilms(films.begin(), films.begin() + n);

    // Executa o Merge Sort
    Mergesort::SortResult result = Mergesort::mergesort(selectedFilms);

    // Exibe os resultados
    std::cout << "Resultados do Merge Sort para " << n << " filmes:" << std::endl;
    std::cout << "Comparações: " << result.comparisons << std::endl;
    std::cout << "Movimentações: " << result.movements << std::endl;
    std::cout << "Duração: " << result.duration << " segundos" << std::endl;
}

int main() {

    // Teste para diferentes valores de N
    for (int n : {5000, 10000, 20000, 40000}) {
        runMergeSortTest(n);
        std::cout << "------------------------" << std::endl;
    }

    return 0;
}
