#include <iostream>
using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

int main()
{
  int w, h, ch;
  unsigned char *data = stbi_load("sky.jpg", &w, &h, &ch, 3);
  if (data == NULL)
  {
    cout << "\nError! Image 'did Not' load.";
    exit(0);
  }
  cout << "\nImage width = " << w << ", Height = " << h << ", Channel = " << ch << endl;

  stbi_write_png("sky.png", w, h, ch, data, w * ch);
  stbi_write_jpg("skynew.jpg", w, h, ch, data, 100);

  // Grid Display
  for (int row = 0; row < h; row += 8)
  {
    for (int col = 0; col < w; col += 8)
    {
      int index = (row * w + col) * 3;
      int R = data[index];
      int G = data[index + 1];
      int B = data[index + 2];
      int brightness = (R + G + B) / 3;
      int characterindex = brightness * 9 / 256;

      char c = ' ';
      string chars = " .:−=+*#@";
      if (brightness >= 0 && brightness <= 27)
        c = ' ';
      else if (brightness >= 28 && brightness <= 55)
        c = '.';
      else if (brightness >= 56 && brightness <= 83)
        c = ':';
      else if (brightness >= 84 && brightness <= 111)
        c = '-';
      else if (brightness >= 112 && brightness <= 139)
        c = '=';
      else if (brightness >= 140 && brightness <= 167)
        c = '+';
      else if (brightness >= 168 && brightness <= 195)
        c = '*';
      else if (brightness >= 196 && brightness <= 223)
        c = '#';
      else
        c = '@';

      cout << c;
    }
  }

  stbi_image_free(data);
  return 0;
}
