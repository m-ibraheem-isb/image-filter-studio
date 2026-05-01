#pragma once
#include "Filter.h"

class GrayScaleFilter : public Filter
{
public:
  GrayScaleFilter();
  Image apply(const Image &img) override;
};