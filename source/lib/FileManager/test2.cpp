#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include "fileManager.h"

// Testa instanciar fileManager com parâmetros errados

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

    assert(std::string(specificFilm.originalTitle) == "Father of the Bride Part II");
    assert(specificFilm.popularity == 8.387519);
    assert(specificFilm.voteAverage == 5.7);
    return 0;
  }
  catch (const std::out_of_range &e)
  {
    std::cout << "Erro de ID: " << e.what() << std::endl;
    return -1;
  }
  catch (const std::runtime_error &e)
  {
    std::cout << "Erro de execução: " << e.what() << std::endl;
    return -1;
  }
  catch (...)
  {
    std::cout << "Erro desconhecido!" << std::endl;
    return -1;
  }
}
