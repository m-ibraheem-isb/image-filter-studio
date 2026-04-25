#pragma once
#include "Filter.h"

class FlipVerticalFilter : public Filter
{
public:
  FlipVerticalFilter();
  Image apply(Image img) override;
};