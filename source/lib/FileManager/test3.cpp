#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include "fileManager.h"

// Testa leitura de todos os filmes

int main()
{
  try
  {
    string csvPath = "../source/data/movies_dataset_min.csv";
    string binaryPath = "../source/data/filmes.bin";
    fileManager manager(csvPath, binaryPath);

    vector<Film> allFilms;
    manager.getAllFilms(allFilms);

    assert(allFilms.size() == 9);
    assert(std::string(allFilms[0].originalTitle) == "Toy Story");
    assert(std::string(allFilms[1].originalTitle) == "Jumanji");
    assert(std::string(allFilms[2].originalTitle) == "Grumpier Old Men");
    assert(std::string(allFilms[3].originalTitle) == "Waiting to Exhale");
    assert(std::string(allFilms[4].originalTitle) == "Father of the Bride Part II");
    assert(std::string(allFilms[5].originalTitle) == "Heat");
    assert(std::string(allFilms[6].originalTitle) == "Sabrina");
    assert(std::string(allFilms[7].originalTitle) == "Tom and Huck");
    assert(std::string(allFilms[8].originalTitle) == "Sudden Death");

    return 0;
  }
  catch (...)
  {
    std::cout << "Erro desconhecido!" << std::endl;
    return -1;
  }
}
