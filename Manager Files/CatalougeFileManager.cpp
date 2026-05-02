#include "CatalougeFileManager.h"
#include <fstream>
#include <sstream>

CatalogueFileManager::CatalogueFileManager()
{
  filePath = "Data/Catalouge.txt";
}

CatalogueFileManager::CatalogueFileManager(string path)
{
  filePath = path;
}

vector<string> CatalogueFileManager::loadCatalogue()
{
  vector<string> records;
  ifstream file(filePath);
  string line;
  getline(file, line);
  while (getline(file, line))
  {
    if (!line.empty())
      records.push_back(line);
  }
  file.close();
  return records;
}

void CatalogueFileManager::saveCatalogue(vector<Filter *> filters)
{
  ofstream file(filePath);
  file << "FilterID|FilterName|Category|IsEnabled" << endl;
  for (int i = 0; i < filters.size(); i++)
  {
    file << filters[i]->getFilterID() << "|"
         << filters[i]->getFilterName() << "|"
         << filters[i]->getCategory() << "|"
         << (filters[i]->isFilterEnabled() ? "1" : "0")
         << endl;
  }
  file.close();
}

void CatalogueFileManager::toggleFilter(int id, bool status)
{
  vector<string> records = loadCatalogue();
  ofstream file(filePath);
  file << "FilterID|FilterName|Category|IsEnabled" << endl;

  for (int i = 0; i < records.size(); i++)
  {
    string fid = "";
    string rest = "";
    int part = 0;

    for (int j = 0; j < records[i].length(); j++)
    {
      if (records[i][j] == '|' && part == 0)
      {
        part++;
        continue;
      }
      if (part == 0)
        fid += records[i][j];
      else
        rest += records[i][j];
    }

    int filterID = 0;
    for (int j = 0; j < fid.length(); j++)
    {
      filterID = filterID * 10 + (fid[j] - '0');
    }

    if (filterID == id)
      file << fid << "|" << rest.substr(0, rest.length() - 1) << "|" << (status ? "1" : "0") << endl;
    else
      file << records[i] << endl;
  }
  file.close();
}