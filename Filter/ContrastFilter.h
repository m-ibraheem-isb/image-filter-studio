#pragma once
#include "Filter.h"

class Contrast : public Filter
{
private:
  int minValue;
  int maxValue;

public:
  Contrast();
  Image apply(Image img) override;
};