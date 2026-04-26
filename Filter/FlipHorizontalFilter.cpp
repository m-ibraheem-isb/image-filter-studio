#include "FlipHorizontalFilter.h"

// Default Constructor:
FlipHorizontalFilter::FlipHorizontalFilter() : Filter(8, "Flip Horizontal", "Geometric", true) {}

// Overloaded apply() Function:
Image FlipHorizontalFilter::apply(Image img)
{
  Pixel temp;
  Image copy = img;
  for (int i = 0; i < img.getHeight() ; i++)
  {
    for (int j = 0; j < img.getWidth() / 2; j++)
    {
      temp = copy.at(i, j);
      copy.at(i, j) = copy.at(i, img.getWidth() - 1 - j);
      copy.at(i, img.getWidth() - 1 - j) = temp;
    }
  }
  return copy;
}