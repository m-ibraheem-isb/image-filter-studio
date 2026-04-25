#pragma once
#include "Filter.h"

class GreenChannelFilter : public Filter
{
public:
  GreenChannelFilter();
  Image apply(Image img) override;
};