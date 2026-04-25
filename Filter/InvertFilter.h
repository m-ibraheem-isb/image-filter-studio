#pragma once
#include "Filter.h"

class InvertFilter : public Filter
{
public:
  InvertFilter();
  Image apply(Image img) override;
};