#include <iostream>
#include "fileManager.h"

using namespace std;

int main()
{
  string csvPath = "../source/data/movies_dataset_min.csv";
  string binaryPath = "../source/data/filmes.bin";

  fileManager fManager(csvPath, binaryPath);

  Film filmeNome = fManager.getFilmeById(2);
  cout << "Nome do filme: " << filmeNome.movieName << " popularidade: " << filmeNome.popularity << " voto_average: " << filmeNome.vote_average << endl;

  return 0;
}
