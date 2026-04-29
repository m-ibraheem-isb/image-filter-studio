#pragma once
#include "Filter.h"

class GreenChannelFilter : public Filter
{
public:
  GreenChannelFilter();
  Image apply(const Image &img) override;
};