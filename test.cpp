#include <iostream>
#include "Core/Pixel.h"
#include "Core/Image.h"
#include "Core/Pixel.h"
#include "Core/Image.h"
#include "Filters/GrayscaleFilter.h"
#include "Filters/InvertFilter.h"
#include "Filters/BrightnessFilter.h"
#include "Filters/ContrastFilter.h"
#include "Filters/RedChannelFilter.h"
#include "Filters/GreenChannelFilter.h"
#include "Filters/BlueChannelFilter.h"
#include "Filters/FlipHorizontalFilter.h"
#include "Filters/FlipVerticalFilter.h"
#include "Filters/BoxBlurFilter.h"
using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
// // #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include "stb_image/stb_image_write.h"

int main()
{
  // int w, h, ch;
  // unsigned char *data = stbi_load("sky.jpg", &w, &h, &ch, 3);
  // if (data == NULL)
  // {
  //   cout << "\nError! Image 'did Not' load.";
  //   exit(0);
  // }
  // cout << "\nImage width = " << w << ", Height = " << h << ", Channel = " << ch << endl;

  // stbi_write_png("sky.png", w, h, ch, data, w * ch);
  // stbi_write_jpg("skynew.jpg", w, h, ch, data, 100);

  // // Grid Display
  // for (int row = 0; row < h; row += 8)
  // {
  //   for (int col = 0; col < w; col += 8)
  //   {
  //     int index = (row * w + col) * 3;
  //     int R = data[index];
  //     int G = data[index + 1];
  //     int B = data[index + 2];
  //     int brightness = (R + G + B) / 3;
  //     int characterindex = brightness * 9 / 256;

  //     char c = ' ';
  //     string chars = " .:−=+*#@";
  //     if (brightness >= 0 && brightness <= 27)
  //       c = ' ';
  //     else if (brightness >= 28 && brightness <= 55)
  //       c = '.';
  //     else if (brightness >= 56 && brightness <= 83)
  //       c = ':';
  //     else if (brightness >= 84 && brightness <= 111)
  //       c = '-';
  //     else if (brightness >= 112 && brightness <= 139)
  //       c = '=';
  //     else if (brightness >= 140 && brightness <= 167)
  //       c = '+';
  //     else if (brightness >= 168 && brightness <= 195)
  //       c = '*';
  //     else if (brightness >= 196 && brightness <= 223)
  //       c = '#';
  //     else
  //       c = '@';

  //     cout << c;
  //   }
  // }

  // stbi_image_free(data);
  // return 0;

  // Pixel c2(201, 202, 203);
  // Pixel c1(101,102,103);
  // Pixel c3 = c1 + c2;
  // cout << c3;

  // // Create image 5x5
  // Image img2(5, 5);

  // // Set pixel (0,0) to red
  // img2.at(0, 0).setR(255);
  // img2.at(0, 0).setG(0);
  // img2.at(0, 0).setB(0);

  // // Get pixel back
  // int r = img2.at(0, 0).getR();
  // int g = img2.at(0, 0).getG();
  // int b = img2.at(0, 0).getB();

  // // Print values
  // cout << r << " " << g << " " << b << endl;

  // Image c1(7, 4);
  // cout << c1.getHeight();
  // cout << c1.getWidth();

  // Image image(20, 10);
  // for (int i = 0; i < image.getHeight();i++)
  // {
  //   for (int j = 0; j < image.getWidth();j++)
  //   {
  //     image.at(i, j).setR(255);
  //     image.at(i, j).setG(255);
  //     image.at(i, j).setB(255);
  //   }
  // }

  // image.displayASCII();

  // Image c1(5, 5);
  // c1.at(0, 0).setR(255);
  // c1.at(0, 0).setG(0);
  // c1.at(0, 0).setB(0);

  // Image c2 = c1;
  // // c2.at(0, 0).setR(0);
  // // c2.at(0, 0).setG(255);
  // // c2.at(0, 0).setB(255);

  // cout << c2.at(0, 0).getR() << endl;
  // cout << c2.at(0, 0).getG() << endl;
  // cout << c2.at(0, 0).getB();

  // Image img(100, 100);
  // for (int i = 0; i < 100; i++)
  // {
  //   for (int j = 0; j < 100; j++)
  //   {
  //     img.at(i, j).setR(255);
  //     img.at(i, j).setG(0);
  //     img.at(i, j).setB(0);
  //   }
  // }
  // img.save("testoutput.jpg");

  int w, h, ch;
  unsigned char *data = stbi_load("sky.jpg", &w, &h, &ch, 3);
  if (data == NULL)
  {
    cout << "\nError! Image 'did Not' load.";
    exit(0);
  }
  cout << "\nImage width = " << w << ", Height = " << h << ", Channel = " << ch << endl;

  Image obj1(h, w);

  for (int row = 0; row < h; row++)
  {
    for (int col = 0; col < w; col++)
    {
      int index = (row * w + col) * 3;

      obj1.at(row, col).setR(data[index]);
      obj1.at(row, col).setG(data[index + 1]);
      obj1.at(row, col).setB(data[index + 2]);
    }
  }

  // GrayScaleFilter filter;
  // Image result = filter.apply(obj1);
  // result.save("grayscale_output.png");

  // InvertFilter f1;
  // Image r1 = f1.apply(obj1);
  // r1.save("invert_output.png");

  // BrightnessFilter f2(50);
  // Image r2 = f2.apply(obj1);
  // r2.save("bright_output.png");

  // FlipHorizontalFilter f3;
  // Image r3 = f3.apply(obj1);
  // r3.save("fliph_output.png");

  // FlipVerticalFilter f4;
  // Image r4 = f4.apply(obj1);
  // r4.save("flipv_output.png");

  // Print a few pixel values before applying the filter
  // cout << "Before blur (first 3 pixels):\n";
  // for (int i = 0; i < 3 && i < obj1.getHeight(); ++i)
  // {
  //   for (int j = 0; j < 3 && j < obj1.getWidth(); ++j)
  //   {
  //     cout << "(" << obj1.at(i, j).getR() << "," << obj1.at(i, j).getG() << "," << obj1.at(i, j).getB() << ") ";
  //   }
  //   cout << endl;
  // }

  BoxBlurFilter f5;
  Image r5 = f5.apply(obj1);

  // Print a few pixel values after applying the filter
  cout << "After blur (first 3 pixels):\n";
  for (int i = 0; i < 3 && i < r5.getHeight(); ++i)
  {
    for (int j = 0; j < 3 && j < r5.getWidth(); ++j)
    {
      cout << "(" << r5.at(i, j).getR() << "," << r5.at(i, j).getG() << "," << r5.at(i, j).getB() << ") ";
    }
    cout << endl;
  }

  r5.save("Output Images/blur_output.png");

  // Print a few pixel values before applying the contrast filter
  cout << "Before contrast (first 3 pixels):\n";
  for (int i = 0; i < 3 && i < obj1.getHeight(); ++i)
  {
    for (int j = 0; j < 3 && j < obj1.getWidth(); ++j)
    {
      cout << "(" << obj1.at(i, j).getR() << "," << obj1.at(i, j).getG() << "," << obj1.at(i, j).getB() << ") ";
    }
    cout << endl;
  }

  // ContrastFilter f6;
  // Image r6 = f6.apply(obj1);

  // // Print a few pixel values after applying the contrast filter
  // cout << "After contrast (first 3 pixels):\n";
  // for (int i = 0; i < 3 && i < r6.getHeight(); ++i)
  // {
  //   for (int j = 0; j < 3 && j < r6.getWidth(); ++j)
  //   {
  //     cout << "(" << r6.at(i, j).getR() << "," << r6.at(i, j).getG() << "," << r6.at(i, j).getB() << ") ";
  //   }
  //   cout << endl;
  // }
  // r6.save("contrast_output.png");

  // RedChannelFilter f7;
  // Image r7 = f7.apply(obj1);
  // r7.save("red_output.png");

  // GreenChannelFilter f8;
  // Image r8 = f8.apply(obj1);
  // r8.save("green_output.png");

  // BlueChannelFilter f9;
  // Image r9 = f9.apply(obj1);
  // r9.save("blue_output.png");

  stbi_image_free(data);
}
