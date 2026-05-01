#include "Filter.h"

// Default Constructors:
Filter::Filter() : filterID(0), filterName(" "), Category(" "), isEnabled("False") {}

// Parametrized Constructor:
Filter::Filter(int id, string name, string category, bool enabled ) : filterID(id), filterName(name), Category(category), isEnabled(enabled) {}

// Getters:
int Filter::getFilterID() const
{
  return filterID;
}
string Filter::getFilterName() const
{
  return filterName;
}
string Filter::getCategory() const
{
  return Category;
}
bool Filter::isFilterEnabled() const
{
  return isEnabled;
}

// Setter:
void Filter::setEnabled(bool status)
{
  isEnabled = status;
}

// Destructor:
Filter::~Filter() {}