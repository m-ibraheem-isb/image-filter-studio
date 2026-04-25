#pragma once
#include "Filter.h"

class FlipHorizontalFilter : public Filter
{
public:
  FlipHorizontalFilter();
  Image apply(Image img) override;
};