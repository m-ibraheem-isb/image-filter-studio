#include "Catalouge.h"
#include "../Manager Files/CatalougeFileManager.h"
#include "../Filters/GrayScaleFilter.h"
#include "../Filters/InvertFilter.h"
#include "../Filters/BrightnessFilter.h"
#include "../Filters/ContrastFilter.h"
#include "../Filters/RedChannelFilter.h"
#include "../Filters/GreenChannelFilter.h"
#include "../Filters/BlueChannelFilter.h"
#include "../Filters/FlipHorizontalFilter.h"
#include "../Filters/FlipVerticalFilter.h"
#include "../Filters/BoxBlurFilter.h"
#include <fstream>
#include <sstream>

// Default Constructor:
Catalogue::Catalogue() : filePath( "catalog.txt"){}

// Parametrized Constructor:
Catalogue::Catalogue(string path):  filePath(path){}

// Loading Filter:
void Catalogue::loadFilters()
{
  filters.clear();
  ifstream file(filePath);
  string line;
  getline(file, line);

  while (getline(file, line))
  {
    if (line.empty())
      continue;

    string id = "";
    string name = "";
    string category = "";
    string enabled = "";
    int part = 0;

    for (int i = 0; i < line.length(); i++)
    {
      if (line[i] == '|')
      {
        part++;
        continue;
      }
      if (part == 0)
        id += line[i];
      else if (part == 1)
        name += line[i];
      else if (part == 2)
        category += line[i];
      else if (part == 3)
        enabled += line[i];
    }

    int filterID = 0;
    for (int i = 0; i < id.length(); i++)
    {
      filterID = filterID * 10 + (id[i] - '0');
    }

    bool isEnabled = (enabled == "1");

    Filter *f = nullptr;
    if (filterID == 1)
      f = new GrayScaleFilter();
    else if (filterID == 2)
      f = new InvertFilter();
    else if (filterID == 3)
      f = new BrightnessFilter(30);
    else if (filterID == 4)
      f = new ContrastFilter();
    else if (filterID == 5)
      f = new RedChannelFilter();
    else if (filterID == 6)
      f = new GreenChannelFilter();
    else if (filterID == 7)
      f = new BlueChannelFilter();
    else if (filterID == 8)
      f = new BoxBlurFilter();
    else if (filterID == 9)
      f = new FlipHorizontalFilter();
    else if (filterID == 10)
      f = new FlipVerticalFilter();

    if (f != nullptr)
    {
      f->setEnabled(isEnabled);
      filters.push_back(f);
    }
  }
  file.close();
}

void Catalogue::saveFilters()
{
  CatalogueFileManager cfm(filePath);
  cfm.saveCatalogue(filters);
}

vector<Filter *> Catalogue::getAllFilters()
{
  return filters;
}

vector<Filter *> Catalogue::getEnabledFilters()
{
  vector<Filter *> enabled;
  for (int i = 0; i < filters.size(); i++)
  {
    if (filters[i]->isFilterEnabled())
      enabled.push_back(filters[i]);
  }
  return enabled;
}

void Catalogue::enableFilter(int id)
{
  for (int i = 0; i < filters.size(); i++)
  {
    if (filters[i]->getFilterID() == id)
    {
      filters[i]->setEnabled(true);
      saveFilters();
      return;
    }
  }
}

void Catalogue::disableFilter(int id)
{
  for (int i = 0; i < filters.size(); i++)
  {
    if (filters[i]->getFilterID() == id)
    {
      filters[i]->setEnabled(false);
      saveFilters();
      return;
    }
  }
}

Filter *Catalogue::findFilter(int id)
{
  for (int i = 0; i < filters.size(); i++)
  {
    if (filters[i]->getFilterID() == id)
      return filters[i];
  }
  return nullptr;
}