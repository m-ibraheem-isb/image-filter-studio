#pragma once
#include "Filter.h"

class FlipVerticalFilter : public Filter
{
public:
  FlipVerticalFilter();
  Image apply(const Image &img) override;
  Filter *clone() const override { return new FlipVerticalFilter(*this); }
};