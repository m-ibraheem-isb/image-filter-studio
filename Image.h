#pragma once
#include "Pixel.h"
#include <string>
using namespace std;

class FilterSession;

class Image
{
private:
  Pixel **pixels;
  int width;
  int height;

public:
  Image(int width, int height);
  Image(const Image &other);
  ~Image();

  Pixel &at(int row, int col);
  int getWidth() const;
  int getHeight() const;

  void displayASCII();
  void save(const string &path);

  friend class FilterSession;
};