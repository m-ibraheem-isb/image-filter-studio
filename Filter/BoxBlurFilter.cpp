#include "BoxBlurFilter.h"

// Default Constructor:
BoxBlurFilter::BoxBlurFilter() : Filter(10, "Flip Vertical", "Spatial Filter", true) {}

// Check Boundary:
bool BoxBlurFilter::CheckBoundary(int row, int coloumn, int height, int width)
{
  if ((row >= 0 && row < height) && (coloumn >= 0 && coloumn < width))
    return true;
  return false;
}

// Overloaded apply() Function:
Image BoxBlurFilter::apply(Image img)
{
  Image temp = img;
  int height = img.getHeight();
  int width = img.getWidth();

  for (int i = 0; i < img.getHeight(); i++)
  {
    for (int j = 0; j < img.getWidth(); j++)
    {
      int sumR = 0;
      int sumG = 0;
      int sumB = 0;
      int count = 0;
      for (int dr = -1; dr <= 1; dr++)
      {
        for (int dc = -1; dc <= 1; dc++)
        {
          int NeighbourRow = dc + i;
          int NeighbourColoumn = dr + j;
          if (CheckBoundary(NeighbourRow, NeighbourColoumn, height, width))
          {
            sumR += img.at(NeighbourRow, NeighbourColoumn).getR();
            sumG += img.at(NeighbourRow, NeighbourColoumn).getG();
            sumB += img.at(NeighbourRow, NeighbourColoumn).getB();
            count++;
          }
        }
      }
      temp.at(i, j).setR(sumR / count);
      temp.at(i, j).setG(sumG / count);
      temp.at(i, j).setB(sumB / count);
    }
  }
  return temp;
}