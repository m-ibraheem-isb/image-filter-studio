#include "FilterSession.h"
#include <ctime>

// Constructor:
FilterSession::FilterSession(string Cnic, Image *Img) : cnic(Cnic), image(Img), timestamp(generateTimestamp()) {}

// Destructor:
FilterSession::~FilterSession()
{
  for (int i = 0; i < pipeline.size(); i++)
  {
    delete pipeline[i];
  }
  pipeline.clear();
}
