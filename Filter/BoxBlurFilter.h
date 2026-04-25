#pragma once
#include "Filter.h"

class BoxBlurFilter : public Filter
{
public:
  BoxBlurFilter();
  Image apply(Image img) override;
};