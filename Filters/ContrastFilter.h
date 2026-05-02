#pragma once
#include "Filter.h"

class ContrastFilter : public Filter
{
private:
  int minValue;
  int maxValue;

public:
  ContrastFilter();
  ContrastFilter(int Min, int Max);
  Image apply(const Image &img) override;
  Filter *clone() const override { return new ContrastFilter(*this); }
};