#pragma once
#include <vector>
#include <string>
using namespace std;

class SessionsFileManager
{
private:
  string filePath;
  string cnic;
  string timestamp;
  string filtersApplied;
  string outputFileName;

public:
  SessionsFileManager();
  SessionsFileManager(string path);

  void saveSession(string cnic, string timestamp,
                   string filters, string outputFile);
  vector<string> loadCustomerSessions(string cnic);
  vector<string> loadAllSessions();
};