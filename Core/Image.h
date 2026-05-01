#pragma once
#include "Pixel.h"
#include <string>
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
  ~Image();

  Pixel &at(int row, int col);             // for temp (write)
  const Pixel &at(int row, int col) const; // for img (read)
  int getWidth() const;
  int getHeight() const;

  void displayASCII();
  void save(const string &path);

  friend class FilterSession;
};