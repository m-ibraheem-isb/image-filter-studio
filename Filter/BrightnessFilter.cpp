#include "BrightnessFilter.h"

// Default Constructor:
BrightnessFilter::BrightnessFilter(int value) : Filter(3, "Brightness Adjust", "Pixel Transform", true)
{
  adjustmentValue = value;
}

// Overloaded apply() Function:
Image BrightnessFilter::apply(const Image &img)
{
  Image temp = img;
  for (int i = 0; i < img.getHeight(); i++)
  {
    for (int j = 0; j < img.getWidth(); j++)
    {

      // Getting Values:
      int r = (temp.at(i, j).getR()) + adjustmentValue;
      int g = (temp.at(i, j).getG()) + adjustmentValue;
      int b = (temp.at(i, j).getB()) + adjustmentValue;

      // Setting New Values:
      temp.at(i, j).setR(r);
      temp.at(i, j).setG(g);
      temp.at(i, j).setB(b);
    }
  }
  return temp;
}