#include <iostream>
#include <chrono>
#include <thread>
#include "fileManager.h"
#include "metrics.h"
#include "quicksort.h"
#include "mergesort.h"
#include "heapsort.h"

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
  std::vector<std::string> inputDataString = fileManager.getFileRead("compara_sort.dat");
  std::vector<int> inputData;

  // Converte vetor de strings para vetor de inteiros
  for (int i = 0; i < inputDataString.size(); i++)
  {
    inputData.push_back(std::stoi(inputDataString[i]));
  }

  std::string csvFilename = "movies_dataset.csv";
  std::string binaryFilename = "filmes.bin";
  fileManager.convertCSV2Bin(csvFilename, binaryFilename);

  Metrics metrics;

  for (const auto &nFilms : inputData)
  {
    std::vector<Film> filmsForMerge;
    fileManager.getRandomNFilms(nFilms, filmsForMerge);

    std::vector<Film> filmsForQuick(filmsForMerge);
    std::vector<Film> filmsForHeap(filmsForMerge);
    std::string nFilmString = std::to_string(nFilms);

    auto mergeId = metrics.createBlock("Mergesort - " + nFilmString);
    Mergesort<Film>::mergesort(filmsForMerge, &metrics, mergeId);

    auto quickId = metrics.createBlock("Quicksort - " + nFilmString);
    Quicksort<Film>::quicksort(filmsForQuick, &metrics, quickId);

    auto heapId = metrics.createBlock("Heapsort - " + nFilmString);
    Heapsort<Film>::heapsort(filmsForHeap, &metrics, heapId);
  }

  std::string results = metrics.getFormattedResults();
  fileManager.writeFile("compara_sort.out", results);

  return 0;
}
