#pragma once
#include "../Image.h"
#include <string>
using namespace std;

class ImageFileManager
{
private:
  string filePath;
  int width;
  int height;
  int channels;

  string getFileExtension(string path);

public:
  ImageFileManager();
  ImageFileManager(string path);

  Image loadImage(string path);
  void saveImage(Image &img, string path);
};