#pragma once
#include "Filter.h"

class InvertFilter : public Filter
{
public:
  InvertFilter();
  Image apply(const Image &img) override;
};