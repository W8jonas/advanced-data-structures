#include <iostream>
#include <chrono>
#include <thread>
#include "metrics.h"
#include "quicksort.h"
#include "fileManager.h"

int main()
{
  Metrics testMetrics;

  auto id = testMetrics.createBlock("Bloco 1");

  std::string entryPath = "../source/data/";
  std::string csvFilename = "movies_dataset.csv";
  std::string binaryFilename = "filmes.bin";

  fileManager fm(entryPath);

  fm.convertCSV2Bin(csvFilename, binaryFilename);

  std::vector<Film> films;
  fm.getRandomNFilms(40, films);

  testMetrics.startTimer(id);
  Quicksort<Film>::quicksort(films);
  testMetrics.stopTimer(id);

  for (size_t i = 1; i < 5; ++i)
  {
    std::cout << "Nome do filme: " << films[i].title << " popularidade: " << films[i].popularity << std::endl;
  }

  testMetrics.printResults();

  return 0;
}
