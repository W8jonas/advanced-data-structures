#include <iostream>
#include "fileManager.h"

using namespace std;

int main()
{
  string csvPath = "../source/data/movies_dataset_min.csv";
  string binaryPath = "../source/data/filmes.bin";

  fileManager fManager(csvPath, binaryPath);

  // Lê filme de indice 2
  Film filmeNome = fManager.getFilmeById(2);
  cout << "Nome do filme: " << filmeNome.movieName << " popularidade: " << filmeNome.popularity << " voto_average: " << filmeNome.vote_average << endl;
  cout << endl;

  // Lê N filmes aleatórios
  vector<Film> filmList;
  fManager.getRandomNFilms(3, filmList);
  for (int i = 0; i < filmList.size(); i++)
  {
    cout << "Nome do filme: " << filmList[i].movieName << " popularidade: " << filmList[i].popularity << " voto_average: " << filmList[i].vote_average << endl;
  }
  cout << endl;

  // Lê todos os filmes em ordem
  vector<Film> allFilms;
  fManager.getAllFilms(allFilms);
  for (int i = 0; i < allFilms.size(); i++)
  {
    cout << "Nome do filme: " << allFilms[i].movieName << " popularidade: " << allFilms[i].popularity << " voto_average: " << allFilms[i].vote_average << endl;
  }

  return 0;
}
