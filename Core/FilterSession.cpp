#include "FilterSession.h"

// Constructor:
FilterSession::FilterSession(string Cnic, Image *Img) : cnic(Cnic), image(Img) {}

// Destructor:
FilterSession::~FilterSession()
{
  for (int i = 0; i < pipeline.size(); i++)
  {
    delete pipeline[i];
  }
  pipeline.clear();
}
