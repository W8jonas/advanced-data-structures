#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <cstring>
#include "fileManager.h"

// Construtor - verifica inicializa os caminhos dos arquivos e chama convertCSV2Bin
fileManager::fileManager(const string &csvPath, const string &binaryPath)
{

  if (csvPath.empty() || binaryPath.empty())
  {
    std::cout << "Erro: Parâmetros inválidos: Caminho para o CSV ou Binário está vazio." << std::endl;
    throw std::invalid_argument("Parâmetros inválidos: Caminho para o CSV ou Binário está vazio.");
  }

  this->csvFilePath = csvPath;
  this->binaryFilePath = binaryPath;

  convertCSV2Bin();
}

string getNextValue(stringstream &ss, std::ifstream &csvFile)
{
  string temp;
  std::getline(ss, temp, ';');
  return temp;
}

bool getNextLine(std::ifstream &csvFile, std::vector<string> &csvLineData)
{
  string line;
  std::getline(csvFile, line);
  stringstream ss(line);

  // pega a linha completa e vai passando as colunas para o array;
  for (size_t i = 0; i < 18; i++)
  {
    string value = getNextValue(ss, csvFile);
    if (value.empty())
    {
      return true;
    }
    csvLineData.push_back(value);
  }
  return false;
}

void fileManager::convertCSV2Bin()
{
  std::ifstream csvFile;
  csvFile.open(csvFilePath);
  if (!csvFile.is_open())
  {
    std::cout << "Erro ao abrir o arquivo CSV! " << csvFilePath << std::endl;
    throw std::runtime_error("Erro ao abrir o arquivo CSV.");
  }

  std::ofstream binaryFile;
  binaryFile.open(binaryFilePath, std::ios::binary);
  if (!binaryFile.is_open())
  {
    std::cout << "Erro ao abrir o arquivo binário para escrita! " << binaryFilePath << std::endl;
    throw std::runtime_error("Erro ao abrir o arquivo binário para escrita.");
  }

  string header;
  std::getline(csvFile, header);

  bool error = false;
  while (!error)
  {
    std::vector<string> csvLineData;
    error = getNextLine(csvFile, csvLineData);

    std::cout << "getNextLine - error: " << error << std::endl;
    if (error)
      break;

    csvLineData.erase(csvLineData.begin());

    for (size_t i = 0; i < csvLineData.size(); i++)
    {
      std::cout << "csvLineData :" << i << " " << csvLineData[i] << std::endl;
    }

    Film film = {};

    film.adult = (csvLineData[0] == "True");
    strncpy(film.genres, csvLineData[1].c_str(), sizeof(film.genres));
    film.databaseId = std::stoi(csvLineData[2]);
    strncpy(film.imdbId, csvLineData[3].c_str(), sizeof(film.imdbId));
    strncpy(film.originalLanguage, csvLineData[4].c_str(), sizeof(film.originalLanguage));
    strncpy(film.originalTitle, csvLineData[5].c_str(), sizeof(film.originalTitle));
    strncpy(film.overview, csvLineData[6].c_str(), sizeof(film.overview) - 1);
    film.popularity = std::stod(csvLineData[7]);
    strncpy(film.productionCompanies, csvLineData[8].c_str(), sizeof(film.productionCompanies));
    strncpy(film.productionCountries, csvLineData[9].c_str(), sizeof(film.productionCountries));
    film.yearOfRelease = std::stoi(csvLineData[10].substr(0, 4)); // Extrai os 4 primeiros caracteres (ano)
    film.revenue = std::stod(csvLineData[11]);
    film.runtime = std::stoi(csvLineData[12]);
    strncpy(film.spokenLanguages, csvLineData[13].c_str(), sizeof(film.spokenLanguages));
    strncpy(film.title, csvLineData[14].c_str(), sizeof(film.title));
    film.voteAverage = std::stod(csvLineData[15]);
    film.voteCount = std::stoi(csvLineData[16]);

    binaryFile.write(reinterpret_cast<char *>(&film), sizeof(Film));
  }
  csvFile.close();
  binaryFile.close();
  std::cout << "FINALIZOU convertCSV2Bin" << std::endl;
}

// Método privado para carregar filmes do arquivo CSV

// Método para obter um filme pelo ID sendo ID o índice do vetor
Film fileManager::getFilmeById(int id)
{
  std::ifstream binaryFile;
  binaryFile.open(binaryFilePath, std::ios::binary);
  if (!binaryFile.is_open())
  {
    std::cout << "Erro ao abrir o arquivo binário!" << std::endl;
    throw std::runtime_error("Erro ao abrir o arquivo binário para escrita.");
  }

  binaryFile.seekg(id * sizeof(Film), std::ios::beg);

  Film film;
  binaryFile.read(reinterpret_cast<char *>(&film), sizeof(Film));

  // verifica se o filme encontrado tem nome, se não tiver nome é sinal que não foi encontrado o filme
  if (!film.originalTitle)
  {
    std::cout << "ID do filme inválido!" << std::endl;
    throw std::out_of_range("ID do filme inválido.");
  }

  binaryFile.close();
  return film;
}

// Método para obter 'n' filmes aleatórios
void fileManager::getRandomNFilms(int n, std::vector<Film> &filmArray)
{
  std::ifstream binaryFile;
  binaryFile.open(binaryFilePath, std::ios::binary);
  if (!binaryFile.is_open())
  {
    std::cout << "Erro ao abrir o arquivo binário!" << std::endl;
    throw std::runtime_error("Erro ao abrir o arquivo binário para escrita.");
  }

  binaryFile.seekg(0, std::ios::end);
  int fileSize = binaryFile.tellg();
  int numFilms = fileSize / sizeof(Film);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, numFilms - 1);

  for (int i = 0; i < n; ++i)
  {
    int randomIndex = distrib(gen);

    // Ler o filme aleatório
    binaryFile.seekg(randomIndex * sizeof(Film), std::ios::beg);
    Film film;
    binaryFile.read(reinterpret_cast<char *>(&film), sizeof(Film));

    if (!film.originalTitle)
    {
      throw std::runtime_error("Erro ao ler o filme aleatório do arquivo binário!");
    }

    filmArray.push_back(film); // Adicionar o filme à lista
  }

  binaryFile.close();
}

// Método para obter todos os filmes
void fileManager::getAllFilms(std::vector<Film> &filmArray)
{
  std::ifstream binaryFile;
  binaryFile.open(binaryFilePath, std::ios::binary);
  if (!binaryFile.is_open())
  {
    std::cout << "Erro ao abrir o arquivo binário!" << std::endl;
    throw std::runtime_error("Erro ao abrir o arquivo binário para escrita.");
  }

  binaryFile.seekg(0, std::ios::end);
  int fileSize = binaryFile.tellg();
  int numFilms = fileSize / sizeof(Film);

  binaryFile.seekg(0, std::ios::beg);

  for (int i = 0; i < numFilms; ++i)
  {
    Film film;
    binaryFile.read(reinterpret_cast<char *>(&film), sizeof(Film));

    if (binaryFile.gcount() < sizeof(Film))
    {
      throw std::runtime_error("Erro ao ler um filme do arquivo binário!");
    }

    filmArray.push_back(film);
  }

  binaryFile.close();
}
