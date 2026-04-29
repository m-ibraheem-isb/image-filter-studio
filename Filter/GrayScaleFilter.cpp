#include "GrayScaleFilter.h"

// Default Constructor:
GrayScaleFilter::GrayScaleFilter() : Filter(1, "Grayscale", "Pixel Transform", true)
{
}

// Overloaded apply() Function:
Image GrayScaleFilter::apply(const Image &img)
{
  Image temp = img;
  for (int i = 0; i < img.getHeight(); i++)
  {
    for (int j = 0; j < img.getWidth(); j++)
    {
      int r = temp.at(i, j).getR();
      int g = temp.at(i, j).getG();
      int b = temp.at(i, j).getB();
      int GreySacle = (r + g + b) / 3;

      temp.at(i, j).setR(GreySacle);
      temp.at(i, j).setG(GreySacle);
      temp.at(i, j).setB(GreySacle);
    }
  }
  return temp;
}