#include "ContrastFilter.h"

// Default Constructor:
ContrastFilter::ContrastFilter() : Filter(4, "Contrast Stretch", "Pixel Transform", true), minValue(0), maxValue(255) {}

// Parametrized Constructor:
ContrastFilter::ContrastFilter(int Min, int Max) : Filter(4, "Contrast Stretch", "Pixel Transform", true)
{
  minValue = Min;
  maxValue = Max;
}

Image ContrastFilter::apply(const Image &img)
{
  Image temp = img;

  int minR = 255, minG = 255, minB = 255;
  int maxR = 0, maxG = 0, maxB = 0;

  // ===== First Pass =====
  for (int i = 0; i < img.getHeight(); i++)
  {
    for (int j = 0; j < img.getWidth(); j++)
    {
      int r = temp.at(i, j).getR();
      int g = temp.at(i, j).getG();
      int b = temp.at(i, j).getB();

      if (r < minR)
        minR = r;
      if (g < minG)
        minG = g;
      if (b < minB)
        minB = b;

      if (r > maxR)
        maxR = r;
      if (g > maxG)
        maxG = g;
      if (b > maxB)
        maxB = b;
    }
  }

  // Prevent division by zero
  if (maxR == minR)
    maxR++;
  if (maxG == minG)
    maxG++;
  if (maxB == minB)
    maxB++;

  // ===== Second Pass =====
  for (int i = 0; i < img.getHeight(); i++)
  {
    for (int j = 0; j < img.getWidth(); j++)
    {
      int r = temp.at(i, j).getR();
      int g = temp.at(i, j).getG();
      int b = temp.at(i, j).getB();

      int newR = (r - minR) * 255 / (maxR - minR);
      int newG = (g - minG) * 255 / (maxG - minG);
      int newB = (b - minB) * 255 / (maxB - minB);

      temp.at(i, j).setR(newR);
      temp.at(i, j).setG(newG);
      temp.at(i, j).setB(newB);
    }
  }

  return temp;
}