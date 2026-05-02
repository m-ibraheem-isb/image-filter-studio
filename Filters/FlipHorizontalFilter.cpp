#include "FlipHorizontalFilter.h"

// Default Constructor:
FlipHorizontalFilter::FlipHorizontalFilter() : Filter(9, "Flip Horizontal", "Geometric", true) {}

// Overloaded apply() Function:
Image FlipHorizontalFilter::apply(const Image &img)
{
  Pixel temp;
  Image copy = img;
  int height = img.getHeight();
  int width = img.getWidth();
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width / 2; j++)
    {
      temp = copy.at(i, j);
      copy.at(i, j) = copy.at(i, width - 1 - j);
      copy.at(i, width - 1 - j) = temp;
    }
  }
  return copy;
}