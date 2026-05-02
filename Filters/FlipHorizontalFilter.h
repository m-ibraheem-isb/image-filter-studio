#pragma once
#include "Filter.h"

class FlipHorizontalFilter : public Filter
{
public:
  FlipHorizontalFilter();
  Image apply(const Image &img) override;
  Filter *clone() const override { return new FlipHorizontalFilter(*this); }
};