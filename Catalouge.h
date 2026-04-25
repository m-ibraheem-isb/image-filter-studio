#pragma once
#include "Filter/Filter.h"
#include <vector>
#include <string>
using namespace std;

class Catalogue
{
private:
  vector<Filter *> filters;
  string filePath;

public:
  Catalogue();
  Catalogue(string path);

  void loadFilters();
  void saveFilters();

  vector<Filter *> getAllFilters();
  vector<Filter *> getEnabledFilters();

  void enableFilter(int id);
  void disableFilter(int id);
  Filter *findFilter(int id);
};