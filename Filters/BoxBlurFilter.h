#pragma once
#include "Filter.h"

class BoxBlurFilter : public Filter
{
public:
  BoxBlurFilter();

  bool CheckBoundary(int row, int coloumn, int height, int width);
  Image apply(const Image &img) override;
  Filter *clone() const override { return new BoxBlurFilter(*this); }
};