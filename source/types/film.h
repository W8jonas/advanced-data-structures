#ifndef FILM_H
#define FILM_H

typedef struct
{
  bool adult;
  char genres[151];
  unsigned int databaseId;
  char imdbId[10];
  char originalLanguage[5];
  char originalTitle[51];
  char overview[500];
  double popularity;
  char productionCompanies[50];
  char productionCountries[50];
  unsigned int yearOfRelease;
  double revenue;
  unsigned int runtime;
  char spokenLanguages[50];
  char title[50];
  double voteAverage;
  unsigned int voteCount;
} Film;

#endif // FILM_H
