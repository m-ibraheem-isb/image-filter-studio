#pragma once
#include "Filter.h"

class RedChannelFilter : public Filter
{
public:
  RedChannelFilter();
  Image apply(const Image &img) override;
};