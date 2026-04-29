// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#include "Image.h"

// Default Constructor:
Image::Image() : pixels(nullptr), height(0), width(0) {}

// Parametrized Constructor:
Image::Image(int Height, int Width) : height(Height), width(Width)
{
  pixels = new Pixel *[height];
  for (int i = 0; i < height; i++)
  {
    pixels[i] = new Pixel[width];
  }
}

// Copy Constructor:
Image::Image(const Image &P)
{
  height = P.height;
  width = P.width;

  pixels = new Pixel *[height];

  for (int i = 0; i < height; i++)
  {
    pixels[i] = new Pixel[width];
    for (int j = 0; j < width; j++)
    {
      pixels[i][j] = P.pixels[i][j];
    }
  }
}

// Destructor:
Image::~Image()
{
  for (int i = 0; i < height; i++)
  {
    delete[] pixels[i];
  }
  delete[] pixels;
}

// Object Return:
Pixel &Image::at(int row, int col)
{
  return pixels[row][col];
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

// Display Ascii:
void Image::displayASCII()
{
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      cout << pixels[i][j];
    }
    cout << endl;
  }
}

// ====== Saving Data ======:
void Image::save(const string &path)
{
  unsigned char *data = new unsigned char[height * width * 3];
  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < width; col++)
    {
      int index = (row * width + col) * 3;
      data[index] = pixels[row][col].getR();
      data[index + 1] = pixels[row][col].getG();
      data[index + 2] = pixels[row][col].getB();
    }
  }

  cout << "Inside save, path = " << path << endl;              // ADD THIS
  cout << "Width: " << width << " Height: " << height << endl; // ADD THIS

  int n = path.length();
  if (path[n - 4] == '.' && path[n - 3] == 'p' && path[n - 2] == 'n' && path[n - 1] == 'g')
  {
    int res = stbi_write_png(path.c_str(), width, height, 3, data, width * 3);
    cout << "PNG write result: " << res << endl; // ADD THIS
  }

  delete[] data;
}