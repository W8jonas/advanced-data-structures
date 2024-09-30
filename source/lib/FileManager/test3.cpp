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
    std::string entryPath = "../source/data/";
    std::string csvFilename = "movies_dataset_min.csv";
    std::string binaryFilename = "filmes.bin";

    fileManager manager(entryPath);
    manager.convertCSV2Bin(csvFilename, binaryFilename);

    Film specificFilm = manager.getFilmeById(4);

    std::vector<Film> allFilms;
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
