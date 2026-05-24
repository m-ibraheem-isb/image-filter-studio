#include "Image.h"
#include <iostream>

// Needed for stb_image_write (implementation is in main.cpp)
#include "../stb_image/stb_image_write.h"

using namespace std;

// Default Constructor
Image::Image() : pixels(nullptr), height(0), width(0)
{
  cout << "[Image] Default constructor called." << endl;
}

// Parameterised Constructor
Image::Image(int Height, int Width) : height(Height), width(Width)
{
  cout << "[Image] Parameterised constructor: " << Width << "x" << Height << endl;
  pixels = new Pixel *[height];
  for (int i = 0; i < height; i++)
    pixels[i] = new Pixel[width];
}

// Copy Constructor (deep copy)
Image::Image(const Image &other) : height(other.height), width(other.width)
{
  cout << "[Image] Copy constructor called." << endl;
  pixels = new Pixel *[height];
  for (int i = 0; i < height; i++)
  {
    pixels[i] = new Pixel[width];
    for (int j = 0; j < width; j++)
      pixels[i][j] = other.pixels[i][j];
  }
}

Image &Image::operator=(const Image &other)
{
  if (this == &other)
    return *this;

  // Free old memory
  for (int i = 0; i < height; i++)
    delete[] pixels[i];
  delete[] pixels;

  // Deep-copy from other
  height = other.height;
  width  = other.width;
  pixels = new Pixel *[height];
  for (int i = 0; i < height; i++)
  {
    pixels[i] = new Pixel[width];
    for (int j = 0; j < width; j++)
      pixels[i][j] = other.pixels[i][j];
  }
  return *this;
}

// Destructor
Image::~Image()
{
  cout << "[Image] Destructor called (" << width << "x" << height << ")." << endl;
  if (pixels)
  {
    for (int i = 0; i < height; i++)
      delete[] pixels[i];
    delete[] pixels;
    pixels = nullptr;
  }
}

Pixel &Image::at(int row, int col)       { return pixels[row][col]; }
const Pixel &Image::at(int row, int col) const { return pixels[row][col]; }
int Image::getWidth()  const { return width;  }
int Image::getHeight() const { return height; }

void Image::displayASCII() const
{
  const int MAX_COLS = 80;
  const int MAX_ROWS = 30;

  int stepCol = (width  > MAX_COLS) ? (width  / MAX_COLS) : 1;
  int stepRow = (height > MAX_ROWS) ? (height / MAX_ROWS) : 1;

  int dispCols = width  / stepCol;
  int dispRows = height / stepRow;

  cout << "\n=== ASCII Preview (" << dispCols << " x " << dispRows << ") ===" << endl;
  for (int i = 0; i < height; i += stepRow)
  {
    for (int j = 0; j < width; j += stepCol)
      cout << pixels[i][j];
    cout << "\n";
  }
  cout << "Image size: " << width << " x " << height
       << " | Total pixels: " << (width * height) << endl;
}

// Save to PNG or JPG
void Image::save(const string &path)
{
  if (!pixels || width == 0 || height == 0)
  {
    cout << "Error: No image data to save." << endl;
    return;
  }

  unsigned char *data = new unsigned char[height * width * 3];
  for (int row = 0; row < height; row++)
    for (int col = 0; col < width; col++)
    {
      int idx = (row * width + col) * 3;
      data[idx]     = (unsigned char)pixels[row][col].getR();
      data[idx + 1] = (unsigned char)pixels[row][col].getG();
      data[idx + 2] = (unsigned char)pixels[row][col].getB();
    }

  int n = (int)path.length();
  bool saved = false;

  if (n >= 4 && path.substr(n - 4) == ".png")
  {
    int res = stbi_write_png(path.c_str(), width, height, 3, data, width * 3);
    saved = (res != 0);
    cout << (saved ? "PNG saved: " : "PNG save FAILED: ") << path << endl;
  }
  else if (n >= 4 && path.substr(n - 4) == ".jpg")
  {
    int res = stbi_write_jpg(path.c_str(), width, height, 3, data, 95);
    saved = (res != 0);
    cout << (saved ? "JPG saved: " : "JPG save FAILED: ") << path << endl;
  }
  else
  {
    cout << "Unsupported extension. Use .png or .jpg" << endl;
  }

  delete[] data;
}
