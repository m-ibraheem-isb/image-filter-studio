#pragma once
#include "../Filters/Filter.h"
#include <vector>
#include <string>
using namespace std;

class CatalogueFileManager
{
private:
  string filePath;

public:
  CatalogueFileManager();
  CatalogueFileManager(string path);

  vector<string> loadCatalogue();
  void saveCatalogue(vector<Filter *> filters);
  void toggleFilter(int id, bool status);
};