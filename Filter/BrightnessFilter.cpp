#include "BrightnessFilter.h"

// Default Constructor:
BrightnessFilter::BrightnessFilter(int value) : Filter(3, "Brightness Adjust", "Pixel Transform", true)
{
  adjustmentValue = value;
}

// Overloaded apply() Function:
Image BrightnessFilter::apply(Image img)
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

      // Clamp Checking:
      int NewR = temp.at(i, j).clamp(r);
      int NewG = temp.at(i, j).clamp(g);
      int NewB = temp.at(i, j).clamp(b);

      // Setting New Values:
      temp.at(i, j).setR(NewR);
      temp.at(i, j).setG(NewR);
      temp.at(i, j).setB(NewR);
    }
  }
  return temp;
}