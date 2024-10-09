#include <iostream>
#include "fileManager.h"

int main()
{
  std::string csvPath = "../source/data/movies_dataset.csv";
  std::string binaryPath = "../source/data/filmes.bin";

  try
  {
    fileManager fManager(csvPath, binaryPath);

    // Lê filme de indice 4
    Film specificFilm = fManager.getFilmeById(4);
    std::cout << "Nome do filme: " << specificFilm.originalTitle << " popularidade: " << specificFilm.popularity << " voto_average: " << specificFilm.voteAverage << std::endl;
    std::cout << std::endl;

    // Lê N filmes aleatórios
    std::vector<Film> filmList;
    fManager.getRandomNFilms(3, filmList);
    for (int i = 0; i < filmList.size(); i++)
    {
      std::cout << "Nome do filme: " << filmList[i].originalTitle << " popularidade: " << filmList[i].popularity << " voto_average: " << filmList[i].voteAverage << std::endl;
    }
    std::cout << std::endl;

    // Lê todos os filmes em ordem
    std::vector<Film> allFilms;
    fManager.getAllFilms(allFilms);
    for (int i = 0; i < allFilms.size(); i++)
    {
      std::cout << "Nome do filme: " << allFilms[i].originalTitle << " popularidade: " << allFilms[i].popularity << " voto_average: " << allFilms[i].voteAverage << std::endl;
    }
  }
  catch (const std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
