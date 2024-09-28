#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "film.h"

using namespace std;

class fileManager
{
public:
  fileManager(const string &csvPath, const string &binaryPath);
  Film getFilmeById(int id);
  void getRandomNFilms(int n, vector<Film> &filmArray);
  void getAllFilms(vector<Film> &filmArray);

private:
  string csvFilePath;
  string binaryFilePath;
  void convertCSV2Bin();
  bool verifyQuotedString(const std::string &string);
  string getNextValue(stringstream &ss, std::ifstream &csvFile);
  bool getNextLine(std::ifstream &csvFile, std::vector<string> &csvLineData);
};

#endif // FILEMANAGER_H
