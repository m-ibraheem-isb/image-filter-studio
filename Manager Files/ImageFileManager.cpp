#include "ImageFileManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

// Default Constructor:
ImageFileManager::ImageFileManager():filePath(""),width(0),height(0),channels(0){}

// Parametrized Constructor:
ImageFileManager::ImageFileManager(string path) : filePath(path){}

// File Extenion:
string ImageFileManager::getFileExtension(string path)
{
  int n = path.length();
  string ext = "";
  ext += path[n - 4];
  ext += path[n - 3];
  ext += path[n - 2];
  ext += path[n - 1];
  return ext;
}

// Loading Image:
Image ImageFileManager::loadImage(string path)
{
  unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 3);

  if (data == nullptr)
  {
    cout << "Error loading image" << endl;
    return Image(1, 1);
  }

  Image img(width, height);

  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < width; col++)
    {
      int index = (row * width + col) * 3;
      img.at(row, col).setR(data[index]);
      img.at(row, col).setG(data[index + 1]);
      img.at(row, col).setB(data[index + 2]);
    }
  }

  stbi_image_free(data);
  return img;
}

// Saving Image:
void ImageFileManager::saveImage(Image &img, string path)
{
  img.save(path);
}