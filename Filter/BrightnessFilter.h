#pragma once
#include "Filter.h"

class BrightnessFilter : public Filter
{
private:
  int adjustmentValue;

public:
  BrightnessFilter(int value);
  Image apply(Image img) override;
  int getAdjustmentValue() const;
};