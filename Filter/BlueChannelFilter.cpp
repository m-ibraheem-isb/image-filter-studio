#include "BlueChannelFilter.h"

// Default Constructor:
BlueChannelFilter::BlueChannelFilter() : Filter(7, "Blue Channel Only", "Pixel Transform", true) {}

// Overloaded apply() Function:
Image BlueChannelFilter::apply(Image img)
{
  Image temp = img;
  for (int i = 0; i < img.getHeight(); i++)
  {
    for (int j = 0; j < img.getWidth(); j++)
    {
      int b = temp.at(i, j).getB();

      temp.at(i, j).setR(0);
      temp.at(i, j).setG(0);
      temp.at(i, j).setB(b);
    }
  }
  return temp;
}