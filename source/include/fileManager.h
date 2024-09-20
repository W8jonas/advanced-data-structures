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
  vector<Film> films;
};

#endif // FILEMANAGER_H
