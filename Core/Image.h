#pragma once
#include "Pixel.h"
#include <string>
#include <iostream>
using namespace std;

class FilterSession;

class Image
{
private:
  Pixel **pixels;
  int height;
  int width;

public:
  Image();
  Image(int height, int width);
  Image(const Image &other);
  Image &operator=(const Image &other);
  ~Image();

  Pixel &at(int row, int col);
  const Pixel &at(int row, int col) const;
  int getWidth() const;
  int getHeight() const;

  void displayASCII() const;
  void save(const string &path);

  friend class FilterSession;
};
