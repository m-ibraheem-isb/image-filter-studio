#include "InvertFilter.h"

// Default Constructor:
InvertFilter::InvertFilter() : Filter(2, "Inver Filter", "Pixel Transform", true) {}

// Overloaded apply() Function:
Image InvertFilter::apply(const Image &img)
{
  Image temp = img;
  for (int i = 0; i < img.getHeight(); i++)
  {
    for (int j = 0; j < img.getWidth(); j++)
    {
      int r = 255 - (img.at(i, j).getR());
      int g = 255 - (img.at(i, j).getG());
      int b = 255 - (img.at(i, j).getB());

      temp.at(i, j).setR(r);
      temp.at(i, j).setG(g);
      temp.at(i, j).setB(b);
    }
  }
  return temp;
}