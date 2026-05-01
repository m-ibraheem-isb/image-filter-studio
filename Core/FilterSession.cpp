#include "FilterSession.h"
#include "../Manager Files/SessionsFileManager.h"
#include <ctime>

FilterSession::FilterSession(string cnic, Image *img)
{
  this->cnic = cnic;
  this->image = img;
  this->timestamp = generateTimestamp();
  this->outputFileName = cnic + "_" + timestamp + ".png";
}

FilterSession::~FilterSession()
{
  pipeline.clear();
}

string FilterSession::generateTimestamp()
{
  time_t now = time(0);
  tm *ltm = localtime(&now);
  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", ltm);
  return string(buffer);
}

string FilterSession::generateOutputFileName()
{
  return outputFileName;
}

FilterSession &FilterSession::addFilter(Filter *f)
{
  pipeline.push_back(f);
  return *this;
}

void FilterSession::displayPipeline()
{
  cout << "[ ";
  for (int i = 0; i < pipeline.size(); i++)
  {
    cout << pipeline[i]->getFilterName();
    if (i < pipeline.size() - 1)
      cout << " -> ";
  }
  cout << " ]" << endl;
}

void FilterSession::applyAll()
{
  for (int i = 0; i < pipeline.size(); i++)
  {
    if (pipeline[i]->isFilterEnabled())
    {
      *image = pipeline[i]->apply(*image);
    }
  }
}

void FilterSession::saveResult(const string &path)
{
  image->save(outputFileName);
  SessionsFileManager Saver("sessions.txt");
  string filtersApplied = "";
  for (int i = 0; i < pipeline.size(); i++)
  {
    filtersApplied += pipeline[i]->getFilterName();
    if (i < pipeline.size() - 1)
      filtersApplied += ">";
  }
  Saver.saveSession(cnic, timestamp, filtersApplied, outputFileName);
}