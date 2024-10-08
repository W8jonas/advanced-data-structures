#include "fileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <cstring>

// Construtor - verifica inicializa os caminhos dos arquivos e chama convertCSV2Bin
fileManager::fileManager(const std::string &entryPath)
{
  if (entryPath.empty())
  {
    std::cout << "Erro: Parâmetros inválidos: Caminho para a pasta de arquivos está vazio." << std::endl;
    throw std::invalid_argument("Parâmetros inválidos: Caminho para a pasta de arquivos está vazio.");
  }

  this->entryPath = entryPath;
}

// Método privado para verificar se texto está com aspas corretamente
bool fileManager::verifyQuotedString(const std::string &string)
{
  bool quoted = false;
  for (size_t i = 0; i < string.size(); i++)
  {
    if (string[i] == '"')
    {
      quoted = !quoted;
    }
  }
  return quoted;
}

// Método privado para ler o próximo valor da linha atual e tratar texto entre aspas
std::string fileManager::getNextValue(std::stringstream &ss, std::ifstream &csvFile)
{
  std::string temp;
  std::getline(ss, temp, ';');

  // Faz o processamento do texto aqui!
  // Se começa com '"' então fazemos tratamento;
  if (temp.front() == '"')
  {
    bool quoted = verifyQuotedString(temp);

    // Se quoted for true, significa que aspas estão abertas, ou seja, precisa ser mais conteúdo;
    if (quoted == false)
    {
      return temp;
    }

    int indd = 0;
    char separator;

    while (quoted && indd < 50)
    {
      indd++;
      std::string stringAccumulator;
      std::getline(ss, stringAccumulator, ';');
      separator = ';';

      if (stringAccumulator.empty())
      {
        // deve ler a próxima linha do arquivo CSV porque nessa linha atual já leu tudo e não achou o fim
        std::string line;
        std::getline(csvFile, line);
        separator = '\n';

        std::stringstream newSS(line); // Nova linha de dados
        std::getline(newSS, stringAccumulator, ';');
        ss = std::move(newSS);
      }
      temp = temp + separator + stringAccumulator;

      quoted = verifyQuotedString(temp);
    }

    return temp;
  }
  else
  {
    return temp;
  }
}

// Método privado para ler o conteúdo da linha no CSV
bool fileManager::getNextLine(std::ifstream &csvFile, std::vector<std::string> &csvLineData)
{
  std::string line;
  std::getline(csvFile, line);
  std::stringstream ss(line);

  // pega a linha completa e vai passando as colunas para o array;
  for (size_t i = 0; i < 18; i++)
  {
    std::string value = getNextValue(ss, csvFile);
    if (value.empty())
    {
      return true;
    }
    csvLineData.push_back(value);
  }
  return false;
}

// Método privado para carregar filmes do arquivo CSV
void fileManager::convertCSV2Bin(const std::string &csvFilename, const std::string &binaryFilename)
{
  this->csvFilename = csvFilename;
  this->binaryFilename = binaryFilename;

  std::ifstream csvFile;
  csvFile.open(this->entryPath + csvFilename);
  if (!csvFile.is_open())
  {
    std::cout << "Erro ao abrir o arquivo CSV! " << this->entryPath + csvFilename << std::endl;
    throw std::runtime_error("Erro ao abrir o arquivo CSV.");
  }

  std::ofstream binaryFile;
  binaryFile.open(this->entryPath + binaryFilename, std::ios::binary);
  if (!binaryFile.is_open())
  {
    std::cout << "Erro ao abrir o arquivo binário para escrita! " << this->entryPath + binaryFilename << std::endl;
    throw std::runtime_error("Erro ao abrir o arquivo binário para escrita.");
  }

  std::string header;
  std::getline(csvFile, header);

  bool error = false;
  while (!error)
  {
    std::vector<std::string> csvLineData;
    error = getNextLine(csvFile, csvLineData);

    if (error)
      break;

    csvLineData.erase(csvLineData.begin());

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
}

// Método público para ler arquivo .dat e retornar vetor de string com valores
std::vector<std::string> fileManager::getFileRead(std::string filename)
{
  std::ifstream file;
  file.open(this->entryPath + filename);
  if (!file.is_open())
  {
    std::cout << "Erro ao abrir o arquivo " << this->entryPath + filename << std::endl;
    throw std::runtime_error("Erro ao abrir o arquivo.");
  }

  std::vector<std::string> fileData;
  while (true)
  {
    std::string line;
    std::getline(file, line);

    if (line.empty())
      break;
    fileData.push_back(line);
  }
  file.close();
  return fileData;
}

void fileManager::writeFile(std::string filename, std::string content)
{
  std::ofstream file;
  file.open(this->entryPath + filename);
  if (!file.is_open())
  {
    std::cout << "Erro ao abrir o arquivo " << this->entryPath + filename << std::endl;
    throw std::runtime_error("Erro ao abrir o arquivo.");
  }
  file << content;
  file.close();
}

// Método para obter um filme pelo ID sendo ID o índice do vetor
Film fileManager::getFilmeById(int id)
{
  std::ifstream binaryFile;
  binaryFile.open(this->entryPath + this->binaryFilename, std::ios::binary);
  if (!binaryFile.is_open())
  {
    std::cout << "Erro ao abrir o arquivo binário." << this->entryPath + this->binaryFilename << std::endl;
    throw std::runtime_error("Erro ao abrir o arquivo binário para escrita.");
  }

  binaryFile.seekg(id * sizeof(Film), std::ios::beg);

  Film film;
  binaryFile.read(reinterpret_cast<char *>(&film), sizeof(Film));

  // verifica se o filme encontrado tem nome, se não tiver nome é sinal que não foi encontrado o filme
  if (!film.originalTitle)
  {
    std::cout << "O filme com ID " << id << " não foi encontrado!" << std::endl;
    film = {};
  }

  binaryFile.close();
  return film;
}

// Método para obter N filmes aleatórios e retorná-los em um vetor
void fileManager::getRandomNFilms(int n, std::vector<Film> &filmArray)
{
  std::ifstream binaryFile;
  binaryFile.open(this->entryPath + this->binaryFilename, std::ios::binary);
  if (!binaryFile.is_open())
  {
    std::cout << "Erro ao abrir o arquivo binário." << this->entryPath + this->binaryFilename << std::endl;
    throw std::runtime_error("Erro ao abrir o arquivo binário para escrita.");
  }

  binaryFile.seekg(0, std::ios::end);
  size_t fileSize = binaryFile.tellg();
  size_t totalFilms = fileSize / sizeof(Film);

  std::random_device rd; // Para números aleatórios
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, totalFilms - 1);

  for (int i = 0; i < n; ++i)
  {
    int randomIndex = distrib(gen);
    Film film;
    binaryFile.seekg(randomIndex * sizeof(Film), std::ios::beg);
    binaryFile.read(reinterpret_cast<char *>(&film), sizeof(Film));
    filmArray.push_back(film);
  }

  binaryFile.close();
}

// Método para obter todos os filmes e retorná-los em um vetor
void fileManager::getAllFilms(std::vector<Film> &filmArray)
{
  std::ifstream binaryFile;
  binaryFile.open(this->entryPath + this->binaryFilename, std::ios::binary);
  if (!binaryFile.is_open())
  {
    std::cout << "Erro ao abrir o arquivo binário." << this->entryPath + this->binaryFilename << std::endl;
    throw std::runtime_error("Erro ao abrir o arquivo binário para escrita.");
  }

  binaryFile.seekg(0, std::ios::end);
  size_t fileSize = binaryFile.tellg();
  size_t totalFilms = fileSize / sizeof(Film);
  binaryFile.seekg(0, std::ios::beg);

  for (size_t i = 0; i < totalFilms; ++i)
  {
    Film film;
    binaryFile.read(reinterpret_cast<char *>(&film), sizeof(Film));
    filmArray.push_back(film);
  }

  binaryFile.close();
}

// Método para salvar N overviews aleatórios em um arquivo binário
void fileManager::saveRandomOverviewsToBinary(const std::string &binaryFile, int N)
{
  std::vector<Film> films;
  getRandomNFilms(N, films); // Recupera N filmes aleatórios

  std::ofstream output(this->entryPath + binaryFile, std::ios::binary);
  if (!output.is_open())
  {
    std::cerr << "Erro ao abrir o arquivo binário para escrita.\n"
              << this->entryPath + binaryFile << std::endl;
    return;
  }

  // Escreve as "overviews" dos filmes no arquivo binário
  for (const auto &film : films)
  {
    std::string overview = film.overview; // Acessa diretamente o campo overview
    size_t length = overview.size();
    output.write(reinterpret_cast<const char *>(&length), sizeof(length)); // Escreve o tamanho da string
    output.write(overview.c_str(), length);                                // Escreve a string
  }

  output.close();
}
