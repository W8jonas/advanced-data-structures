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
  char overview[1300];
  double popularity;
  char productionCompanies[51];
  char productionCountries[51];
  unsigned int yearOfRelease;
  double revenue;
  unsigned int runtime;
  char spokenLanguages[51];
  char title[51];
  double voteAverage;
  unsigned int voteCount;
} Film;

#endif // FILM_H
