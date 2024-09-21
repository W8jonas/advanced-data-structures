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
    string csvPath = "../source/data/movies_dataset_min.csv";
    string binaryPath = "../source/data/filmes.bin";
    fileManager manager(csvPath, binaryPath);

    Film specificFilm = manager.getFilmeById(4);

    assert(std::string(specificFilm.movieName) == "Father of the Bride Part II");
    assert(specificFilm.popularity == 8.387519);
    assert(specificFilm.vote_average == 5.7);
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
