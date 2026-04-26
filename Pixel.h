#pragma once
#include <iostream>
using namespace std;

class Pixel
{
private:
  int R;
  int G;
  int B;

public:
  Pixel();
  Pixel(int r, int g, int b);

  int getR() const;
  int getG() const;
  int getB() const;

  void setR(int r);
  void setG(int g);
  void setB(int b);

  char AsciReturn() const;

  static int clamp(int val);
  Pixel operator+(const Pixel &p) const;
  friend ostream &operator<<(ostream &os, const Pixel &p);
};