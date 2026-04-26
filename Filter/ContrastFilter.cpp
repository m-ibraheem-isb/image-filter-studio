#include "ContrastFilter.h"

// Default Constructor:
ContrastFilter::ContrastFilter(int Min, int Max) : Filter(4, "Contrast Stretch", "Pixel Transform", true)
{
  minValue = Min;
  maxValue = Max;
}

// Overloaded apply() Function:
Image ContrastFilter::apply(Image img)
{
  Image temp = img;
  for (int i = 0; i < img.getHeight(); i++)
  {
    for (int j = 0; j < img.getWidth(); j++)
    {

      // Getting Values:
      int r = temp.at(i, j).getR();
      int g = temp.at(i, j).getG();
      int b = temp.at(i, j).getB();

      // Applying Filter:
      int newR = ((r - minValue) / (maxValue - minValue));
      int newG = ((g - minValue) / (maxValue - minValue));
      int newB = ((b - minValue) / (maxValue - minValue));

      // Clamp Checking:
      int ClampR = temp.at(i, j).clamp(newR);
      int ClampG = temp.at(i, j).clamp(newG);
      int ClampB = temp.at(i, j).clamp(newB);

      // Setting New Values:
      temp.at(i, j).setR(ClampR);
      temp.at(i, j).setG(ClampG);
      temp.at(i, j).setB(ClampB);
    }
  }
  return temp;
}