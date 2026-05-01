#pragma once
#include "Filter.h"

class BlueChannelFilter : public Filter
{
public:
  BlueChannelFilter();
  Image apply(const Image &img) override;
};