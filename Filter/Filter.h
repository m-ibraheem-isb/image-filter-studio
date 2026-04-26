#pragma once
#include "../Image.h"
#include <string>
using namespace std;

class Filter
{
private:
  int filterID;
  string filterName;
  string Category;
  bool isEnabled;

public:
  Filter();
  Filter(int id, string name, string category, bool enabled = true);
  virtual ~Filter();

  virtual Image apply(Image img) = 0;

  int getFilterID() const;
  string getFilterName() const;
  string getCategory() const;
  bool isFilterEnabled() const;
  void setEnabled(bool status);
};