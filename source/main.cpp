#include <iostream>
#include "fileManager.h"

using namespace std;

int main()
{
  string csvPath = "../source/data/movies_dataset.csv";
  string binaryPath = "../source/data/filmes.bin";

  try
  {
    fileManager fManager(csvPath, binaryPath);

    // Lê filme de indice 2
    Film specificFilm = fManager.getFilmeById(4);
    std::cout << "Nome do filme: " << specificFilm.originalTitle << " popularidade: " << specificFilm.popularity << " voto_average: " << specificFilm.voteAverage << std::endl;
    std::cout << std::endl;

    // Lê N filmes aleatórios
    vector<Film> filmList;
    fManager.getRandomNFilms(3, filmList);
    for (int i = 0; i < filmList.size(); i++)
    {
      std::cout << "Nome do filme: " << filmList[i].originalTitle << " popularidade: " << filmList[i].popularity << " voto_average: " << filmList[i].voteAverage << std::endl;
    }
    std::cout << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
