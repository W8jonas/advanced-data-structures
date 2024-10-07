#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "film.h"

class fileManager
{
public:
  fileManager(const std::string &entryPath);
  Film getFilmeById(int id);
  void getRandomNFilms(int n, std::vector<Film> &filmArray);
  void getAllFilms(std::vector<Film> &filmArray);
  std::vector<std::string> getFileRead(std::string filename);
  void writeFile(std::string filename, std::string content);
  void convertCSV2Bin(const std::string &csvFilename, const std::string &binaryFilename);
  void saveRandomOverviewsToBinary(const std::string &binaryFile, int N); // Método adicionado

private:
  std::string entryPath;
  std::string csvFilename;
  std::string binaryFilename;
  bool verifyQuotedString(const std::string &string);
  std::string getNextValue(std::stringstream &ss, std::ifstream &csvFile);
  bool getNextLine(std::ifstream &csvFile, std::vector<std::string> &csvLineData);
};

#endif // FILEMANAGER_H
