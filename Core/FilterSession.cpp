#include "FilterSession.h"
#include "../Manager Files/SessionsFileManager.h"
#include <ctime>
#include <iostream>
using namespace std;

FilterSession::FilterSession(string cnic, Image *img)
{
  this->cnic = cnic;
  this->image = img;
  this->timestamp = generateTimestamp();
  this->outputFileName = "Output Images/" + cnic + "_" + timestamp + ".png";
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
  strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", ltm);
  return string(buffer);
}

string FilterSession::generateOutputFileName()
{
  return outputFileName;
}

FilterSession &FilterSession::addFilter(Filter *f)
{
  pipeline.push_back(f);
  return *this; // enables method chaining
}

void FilterSession::displayPipeline()
{
  if (pipeline.empty())
  {
    cout << "Pipeline: (empty)" << endl;
    return;
  }
  cout << "Pipeline: [ ";
  for (int i = 0; i < (int)pipeline.size(); i++)
  {
    cout << pipeline[i]->getFilterName();
    if (i < (int)pipeline.size() - 1)
      cout << " -> ";
  }
  cout << " ]" << endl;
}

void FilterSession::applyAll()
{
  if (pipeline.empty())
  {
    cout << "Pipeline is empty. Nothing to apply." << endl;
    return;
  }

  cout << "\n=== Applying Pipeline ===" << endl;
  for (int i = 0; i < (int)pipeline.size(); i++)
  {
    if (!pipeline[i]->isFilterEnabled())
    {
      cout << "Skipping disabled filter: " << pipeline[i]->getFilterName() << endl;
      continue;
    }
    cout << "\nApplying filter " << (i + 1) << "/" << pipeline.size()
         << ": " << pipeline[i]->getFilterName() << " ..." << endl;

    *image = pipeline[i]->apply(*image); // operator= now deep-copies → no crash

    image->displayASCII();
  }
  cout << "\nAll " << pipeline.size() << " filter(s) applied." << endl;
}

void FilterSession::saveResult(const string & /*path*/)
{
  image->save(outputFileName);
  SessionsFileManager saver("Data/Sesssions.txt");
  string filtersApplied = "";
  for (int i = 0; i < (int)pipeline.size(); i++)
  {
    filtersApplied += pipeline[i]->getFilterName();
    if (i < (int)pipeline.size() - 1)
      filtersApplied += ">";
  }
  saver.saveSession(cnic, timestamp, filtersApplied, outputFileName);
}
