#include "Pixel.h"

// Constructors:
Pixel::Pixel() : R(0), G(0), B(0) {}
Pixel::Pixel(int r, int g, int b) : R(r), G(g), B(b) {}

// Getters:
int Pixel::getR() const
{
  return R;
}
int Pixel::getG() const
{
  return G;
}
int Pixel::getB() const
{
  return B;
}

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
char Pixel::AsciReturn() const
{
  int Ascii = (R + G + B) / 3;

  if (Ascii <= 27)
    return ' ';
  else if (Ascii <= 55)
    return '.';
  else if (Ascii <= 83)
    return ':';
  else if (Ascii <= 111)
    return '-';
  else if (Ascii <= 139)
    return '=';
  else if (Ascii <= 167)
    return '+';
  else if (Ascii <= 195)
    return '*';
  else if (Ascii <= 223)
    return '#';
  else
    return '@';
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
  out << P.AsciReturn();
  return out;
}

// ====== Operator Overloading ======