#pragma once
#include "Filter.h"

class GrayscaleFilter : public Filter
{
public:
  GrayscaleFilter();
  Image apply(Image img) override;
};