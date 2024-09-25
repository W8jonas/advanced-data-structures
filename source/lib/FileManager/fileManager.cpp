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

  int indx = 0;
  string line;
  std::getline(csvFile, line);
  while (std::getline(csvFile, line))
  {
    stringstream ss(line);
    Film film;
    string temp;

    indx++;
    std::cout << " " << std::endl;
    std::cout << " " << std::endl;
    std::cout << "Getline: " << indx << " => " << line << std::endl;

    // Lê e ignora o index
    std::getline(ss, temp, ';');

    // Lê o campo 'adult' e converte para bool
    std::getline(ss, temp, ';');
    film.adult = (temp == "True");

    // Lê o campo 'genres'
    std::getline(ss, temp, ';');
    strncpy(film.genres, temp.c_str(), sizeof(film.genres));

    // Lê o campo 'id'
    std::getline(ss, temp, ';');
    film.databaseId = std::stoi(temp);

    // Lê o campo 'imdb_id'
    std::getline(ss, temp, ';');
    strncpy(film.imdbId, temp.c_str(), sizeof(film.imdbId));

    // Lê o campo 'original_language'
    std::getline(ss, temp, ';');
    strncpy(film.originalLanguage, temp.c_str(), sizeof(film.originalLanguage));

    // Lê o campo 'original_title' (nome do filme)
    std::getline(ss, temp, ';');
    strncpy(film.originalTitle, temp.c_str(), sizeof(film.originalTitle));

    // Lê o campo 'overview'

    /* std::getline(ss, temp, ';'); // Essa leitura pode ser problemática, então use um workaround
    if (temp.front() == '"')
    {
      std::cout << "Situação chata" << std::endl;

      std::string overview;
      overview += temp; // Inicialmente adiciona o primeiro trecho

      std::cout << "temp >> " << temp << temp.back() << std::endl;
      int count = 0;
      while (temp.back() != '"' && temp.back() != '/n' && count < 5)
      { // Continuar até encontrar o fechamento das aspas
        count++;
        std::getline(ss, temp, ';');
        std::cout << "temp while >> " << temp.back() << temp << std::endl;
        overview += ";" + temp; // Reconstruindo o campo "overview"
      }
      std::strncpy(film.overview, overview.c_str(), sizeof(film.overview) - 1);
      film.overview[sizeof(film.overview) - 1] = '\0';
    }
    else
    {
      std::strncpy(film.overview, temp.c_str(), sizeof(film.overview) - 1);
      film.overview[sizeof(film.overview) - 1] = '\0';
    } */

    std::getline(ss, temp, ';');
    // Se começa com '"' e não terminar com '"' é porque encontrou ; no meio do texto.
    // Ou se começa com '"' e termina com '""' é porque encontrou ; no meio do texto.
    std::cout << "\n\n Pré IF ==>>> '" << temp.front() << "' '" << temp.back() << "' '" << temp[temp.size() - 2] << "'" << std::endl;
    std::cout << "Condições: " << (temp.front() == '"') << (temp.back() == '"') << (temp[temp.size() - 2] != '"') << std::endl;

    if ((temp.front() == '"' && temp.back() != '"') ||
        (temp.front() == '"' && temp.back() == '"' && temp[temp.size() - 2] == '"'))
    {
      std::string stringAccumulator;
      std::getline(ss, stringAccumulator, ';');

      // enquanto stringAccumulator não é vazia e stringAccumulator não encontrou '"' no final, leia mais
      std::cout << "\n\n stringAccumulator ==>>> " << stringAccumulator.c_str() << "\n"
                << std::endl;
      while (true)
      {
        temp = temp + ';' + stringAccumulator;
        if (!stringAccumulator.empty() && stringAccumulator.back() == '"' && stringAccumulator[stringAccumulator.size() - 2] != '"')
        {
          std::cout << "if 1" << std::endl;
          break;
        }

        // Se houver uma quebra de linha, continuamos lendo até encontrar o fim do campo
        if (!std::getline(csvFile, line))
        {
          // Caso especial onde a linha termina e ainda não encontramos o fim do campo
          std::cout << "if 2" << std::endl;
          break;
        }

        // std::cout << "stringAccumulator ==> " << stringAccumulator << std::endl;

        std::stringstream newSS(line); // Nova linha de dados
        std::getline(newSS, stringAccumulator, ';');
        ss = std::move(newSS);
      }
    }

    strncpy(film.overview, temp.c_str(), sizeof(film.overview) - 1);
    film.overview[sizeof(film.overview) - 1] = '\0';
    std::cout << "\nParece que leu tudo!! ==>>> \n"
              << temp.c_str() << std::endl;

    // Filmes que a leitura NÃO estão sendo feitas corretamente:
    // 619, 756, 1113, 5453
    if (indx == 5452)
    {
      break;
    }

    // Lê o campo 'popularity'
    std::getline(ss, temp, ';');
    std::cout << "Temp popularity ::::: " << indx << " => " << temp << std::endl;
    film.popularity = std::stod(temp);

    // Lê o campo 'production_companies'
    std::getline(ss, temp, ';');
    if ((temp.front() == '"' && temp.back() != '"') ||
        (temp.front() == '"' && temp.back() == '"' && temp[temp.size() - 2] == '"'))
    {
      std::string stringAccumulator;
      std::getline(ss, stringAccumulator, ';');

      // enquanto stringAccumulator não é vazia e stringAccumulator não encontrou '"' no final, leia mais
      std::cout << "\n\n\n\n stringAccumulator ==>>> " << stringAccumulator.c_str() << "\n"
                << std::endl;
      while (true)
      {
        temp = temp + ';' + stringAccumulator;
        if (!stringAccumulator.empty() && stringAccumulator.back() == '"' && stringAccumulator[stringAccumulator.size() - 2] != '"')
        {
          break;
        }

        // Se houver uma quebra de linha, continuamos lendo até encontrar o fim do campo
        if (!std::getline(csvFile, line))
        {
          // Caso especial onde a linha termina e ainda não encontramos o fim do campo
          break;
        }

        std::stringstream newSS(line); // Nova linha de dados
        std::getline(newSS, stringAccumulator, ';');
        ss = std::move(newSS);
      }
    }
    strncpy(film.productionCompanies, temp.c_str(), sizeof(film.productionCompanies));

    // Lê o campo 'production_countries'
    std::getline(ss, temp, ';');
    strncpy(film.productionCountries, temp.c_str(), sizeof(film.productionCountries));

    // Lê o campo 'release_date' e extrai o ano
    std::getline(ss, temp, ';');
    std::cout << "Temp yearOfRelease ::::: " << indx << " => " << temp << std::endl;
    film.yearOfRelease = std::stoi(temp.substr(0, 4)); // Extrai os 4 primeiros caracteres (ano)

    // Lê o campo 'revenue'
    std::getline(ss, temp, ';');
    std::cout << "Temp revenue ::::: " << indx << " => " << temp << std::endl;
    film.revenue = std::stod(temp);

    // Lê o campo 'runtime'
    std::getline(ss, temp, ';');
    std::cout << "Temp runtime ::::: " << indx << " => " << temp << std::endl;
    film.runtime = std::stoi(temp);

    // Lê o campo 'spoken_languages'
    std::getline(ss, temp, ';');
    strncpy(film.spokenLanguages, temp.c_str(), sizeof(film.spokenLanguages));

    // Lê o título
    std::getline(ss, temp, ';');
    strncpy(film.title, temp.c_str(), sizeof(film.title));

    // Lê o campo 'vote_average'
    std::getline(ss, temp, ';');
    std::cout << "Temp voteAverage ::::: " << indx << " => " << temp << std::endl;
    film.voteAverage = std::stod(temp);

    // Lê o campo 'vote_count'
    std::getline(ss, temp, ';');
    std::cout << "Temp voteCount ::::: " << indx << " => " << temp << std::endl;
    film.voteCount = std::stoi(temp);

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
