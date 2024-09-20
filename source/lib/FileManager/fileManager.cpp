#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
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

// Método privado para carregar filmes do arquivo CSV
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

  string line;
  std::getline(csvFile, line);
  while (std::getline(csvFile, line))
  {
    stringstream ss(line);
    Film film;
    string temp;

    std::getline(ss, temp, ';'); // lê index
    std::getline(ss, temp, ';'); // lê adult
    std::getline(ss, temp, ';'); // lê genres
    std::getline(ss, temp, ';'); // lê id
    std::getline(ss, temp, ';'); // lê imdb_id
    std::getline(ss, temp, ';'); // lê original_language
    std::getline(ss, temp, ';'); // lê original_title
    strncpy(film.movieName, temp.c_str(), sizeof(film.movieName));

    std::getline(ss, temp, ';'); // lê overview
    std::getline(ss, temp, ';'); // lê popularity
    film.popularity = stod(temp);

    std::getline(ss, temp, ';'); // lê production_companies
    std::getline(ss, temp, ';'); // lê production_countries
    std::getline(ss, temp, ';'); // lê release_date
    std::getline(ss, temp, ';'); // lê Revenue
    std::getline(ss, temp, ';'); // lê Runtime
    std::getline(ss, temp, ';'); // lê spoken_languages
    std::getline(ss, temp, ';'); // lê Title
    std::getline(ss, temp, ';'); // lê Vote average
    film.vote_average = stod(temp);
    std::getline(ss, temp, ';'); // lê vote_count

    binaryFile.write(reinterpret_cast<char *>(&film), sizeof(Film));
  }
  csvFile.close();
  binaryFile.close();
}

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
  if (!film.movieName)
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

    if (!film.movieName)
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
}
