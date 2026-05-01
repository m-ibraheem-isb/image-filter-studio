#include "RedChannelFilter.h"

// Default Constructor:
RedChannelFilter::RedChannelFilter() : Filter(5, "Red Channel Only", "Pixel Transform", true) {}

// Overloaded apply() Function:
Image RedChannelFilter::apply(const Image &img)
{
  Image temp = img;
  for (int i = 0; i < img.getHeight(); i++)
  {
    for (int j = 0; j < img.getWidth(); j++)
    {
      int r = temp.at(i, j).getR();

      temp.at(i, j).setR(r);
      temp.at(i, j).setG(0);
      temp.at(i, j).setB(0);
    }
  }
  return temp;
}