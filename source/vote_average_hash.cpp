#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "fileManager.h"
#include "metrics.h"
#include "quicksort.h"
#include "hash.h"

int main(int argc, char *argv[])
{
  std::string entryPath = "";
  if (argc > 1)
  {
    entryPath = argv[1];
    std::cout << "Valor recebido: " << entryPath << std::endl;
  }
  else
  {
    std::cout << "Nenhum valor foi passado como parâmetro!" << std::endl;
    return 1;
  }

  fileManager fileManager(entryPath);
  std::vector<std::string> inputDataString = fileManager.getFileRead("vote_average.dat");
  std::vector<int> inputData;

  // Converte vetor de strings para vetor de inteiros
  for (int i = 0; i < inputDataString.size(); i++)
  {
    inputData.push_back(std::stoi(inputDataString[i]));
  }

  std::string csvFilename = "movies_dataset.csv";
  std::string binaryFilename = "filmes.bin";
  fileManager.convertCSV2Bin(csvFilename, binaryFilename);

  std::ostringstream outFile;
  for (const auto &nFilms : inputData)
  {
    HashTable hashTable(100); // Tamanho da tabela hash

    std::vector<Film> randomFilms;
    fileManager.getRandomNFilms(nFilms, randomFilms);

    for (const auto &film : randomFilms)
    {
      // std::cout << "hashTable.insert " << film.title << film.voteAverage << " " << std::endl;

      // Converte voteAvegare para string e insere na tabela hash
      hashTable.insert(std::to_string(film.voteAverage));
    }

    // Recuperar todas as entradas da tabela hash
    auto entries = hashTable.getAllEntries();

    Quicksort<std::pair<std::string, int>>::quicksort(entries);

    std::string nFilmString = std::to_string(nFilms);

    outFile << "5 vote_average mais frequentes: [" << nFilmString << "]\n";

    std::cout << std::setprecision(9) << std::fixed;
    for (int i = std::max(0, (int)entries.size() - 5); i < entries.size(); i++)
    {
      outFile << "Vote Average: " << entries[i].first << " - Contagem: " << entries[i].second << "\n";
    }
    outFile << "-------------------------------------------\n";
  }

  fileManager.writeFile("vote_average.out", outFile.str());

  return 0;
}
