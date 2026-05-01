#include "FlipVerticalFilter.h"

// Default Constructor:
FlipVerticalFilter::FlipVerticalFilter() : Filter(9, "Flip Vertical", "Geometric", true) {}

// Overloaded apply() Function:
Image FlipVerticalFilter::apply(const Image &img)
{
  Pixel temp;
  Image copy = img;
  int height = img.getHeight();
  int width = img.getWidth();
  for (int i = 0; i < height / 2; i++)
  {
    for (int j = 0; j < width ; j++)
    {
      temp = copy.at(i, j);
      copy.at(i, j) = copy.at(height - 1 - i, j);
      copy.at(height - 1 - i, j) = temp;
    }
  }
  return copy;
}