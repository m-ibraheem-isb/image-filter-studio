#include "Image.h"

// Default Constructor:
Image::Image() : pixels(nullptr), height(0), width(0) {}

// Parametrized Constructor:
Image::Image(int Height, int Width) : height(Height), width(Width)
{
  pixels = new Pixel *[height];
  for (int i = 0; i < height; i++)
  {
    *pixels = new Pixel[width];
  }
}


// Copy Constructor:
Image::Image(const Image &P)
{
  height = P.height;
  width = P.width;
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width;j++)
    {
      pixels[height][width] = P.pixels[height][width];
    }
  }
}

// Destructor:
Image::~Image()
{
  for (int i = 0; i < height; i++)
  {
    delete[] pixels[height];
  }
  delete[] pixels;
}

// Object Return:
Pixel& Image::at(int height, int width)
{
  return pixels[height][width];
}

// Getters:
int Image::getWidth() const
{
  return width;
}
int Image::getHeight() const
{
  return height;
}