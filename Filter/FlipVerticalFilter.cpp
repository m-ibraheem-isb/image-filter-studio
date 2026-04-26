#include "FlipVerticalFilter.h"

// Default Constructor:
FlipVerticalFilter::FlipVerticalFilter() : Filter(9, "Flip Vertical", "Geometric", true) {}

// Overloaded apply() Function:
Image FlipVerticalFilter::apply(Image img)
{
  Pixel temp;
  Image copy = img;
  for (int i = 0; i < img.getHeight(); i++)
  {
    for (int j = 0; j < img.getWidth() / 2; j++)
    {
      temp = copy.at(i, j);
      copy.at(i, j) = copy.at(img.getHeight() -1- i, j);
      copy.at(img.getHeight() - 1 - i, img.getWidth() - 1 - j) = temp;
    }
  }
  return copy;
}