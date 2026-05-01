#pragma once
#include "Image.h"
#include "../Filters/Filter.h"
#include <vector>
#include <string>
using namespace std;

class FilterSession
{
private:
  Image *image;
  vector<Filter *> pipeline;
  string cnic;
  string timestamp;
  string outputFileName;

  string generateTimestamp();

public:
  FilterSession(string Cnic, Image *Img);
  ~FilterSession();

  FilterSession &addFilter(Filter *f);
  void applyAll();
  void saveResult(const string &path);
  void displayPipeline();
  string generateOutputFileName();
};