#include "GreenChannelFilter.h"

// Default Constructor:
GreenChannelFilter::GreenChannelFilter() : Filter(6, "Green Channel Only", "Pixel Transform", true) {}

// Overloaded apply() Function:
Image GreenChannelFilter::apply(Image img)
{
  Image temp = img;
  for (int i = 0; i < img.getHeight(); i++)
  {
    for (int j = 0; j < img.getWidth(); j++)
    {
      int g = temp.at(i, j).getG();

      temp.at(i, j).setR(0);
      temp.at(i, j).setG(g);
      temp.at(i, j).setB(0);
    }
  }
  return temp;
}