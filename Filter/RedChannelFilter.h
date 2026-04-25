#pragma once
#include "Filter.h"

class RedChannelFilter : public Filter
{
public:
  RedChannelFilter();
  Image apply(Image img) override;
};