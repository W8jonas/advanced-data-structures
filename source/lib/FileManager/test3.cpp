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
    assert(std::string(allFilms[0].movieName) == "Toy Story");
    assert(std::string(allFilms[1].movieName) == "Jumanji");
    assert(std::string(allFilms[2].movieName) == "Grumpier Old Men");
    assert(std::string(allFilms[3].movieName) == "Waiting to Exhale");
    assert(std::string(allFilms[4].movieName) == "Father of the Bride Part II");
    assert(std::string(allFilms[5].movieName) == "Heat");
    assert(std::string(allFilms[6].movieName) == "Sabrina");
    assert(std::string(allFilms[7].movieName) == "Tom and Huck");
    assert(std::string(allFilms[8].movieName) == "Sudden Death");

    return 0;
  }
  catch (...)
  {
    std::cout << "Erro desconhecido!" << std::endl;
    return -1;
  }
}
