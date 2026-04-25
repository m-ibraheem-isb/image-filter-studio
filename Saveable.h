#pragma once
#include <string>
using namespace std;

class Saveable
{
public:
  virtual void save(const string &path) = 0;
  virtual ~Saveable() {}
};