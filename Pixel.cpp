#include "Pixel.h"

// Constructors:
Pixel::Pixel() : R(0), G(0), B(0) {}
Pixel::Pixel(int r, int g, int b) : R(r), G(g), B(b) {}

// Getters:
int Pixel::getR() const {}
int Pixel::getG() const {}
int Pixel::getB() const {}

// Setters:
void Pixel::setR(int r)
{
  R = r;
}
void Pixel::setG(int g)
{
  G = g;
}
void Pixel::setB(int b)
{
  B = b;
}

// Clamp Function:
int Pixel::clamp(int val)
{
  if (val < 0)
    return 0;
  else if (val > 255)
    return 255;
  else
    return val;
}

// Ascii Return:
char Pixel::AsciReturn(char c) const
{
  int brightness = (R + G + B) / 3;
  c = ' ';

  if (brightness >= 0 && brightness <= 27)
    c = ' ';
  else if (brightness <= 55)
    c = '.';
  else if (brightness <= 83)
    c = ':';
  else if (brightness <= 111)
    c = '-';
  else if (brightness <= 139)
    c = '=';
  else if (brightness <= 167)
    c = '+';
  else if (brightness <= 195)
    c = '*';
  else if (brightness <= 223)
    c = '#';
  else
    c = '@';

  return c;
}

// ====== Operator Overloading ======

// Operator : "+"
Pixel Pixel::operator+(const Pixel &P) const
{
  Pixel temp;
  temp.R = R + P.R;
  temp.G = G + P.G;
  temp.B = R + P.B;
  return temp;
}

// Operator : "<<"
std::ostream &operator<<(ostream &out, const Pixel &P)
{
  char c = P.AsciReturn(c);
  out << c << endl;
  return out;
}

// ====== Operator Overloading ======