#include "SessionsFileManager.h"
#include <fstream>

SessionsFileManager::SessionsFileManager()
{
  filePath = "sessions.txt";
}

SessionsFileManager::SessionsFileManager(string path)
{
  filePath = path;
}

void SessionsFileManager::saveSession(string cnic, string timestamp,
                                     string filters, string outputFile)
{
  ofstream file(filePath, ios::app);
  file << cnic << "|" << timestamp << "|" << filters << "|" << outputFile << endl;
  file.close();
}

vector<string> SessionsFileManager::loadCustomerSessions(string cnic)
{
  vector<string> sessions;
  ifstream file(filePath);
  string line;

  while (getline(file, line))
  {
    if (line.empty())
      continue;

    string fileCnic = "";
    for (int i = 0; i < line.length(); i++)
    {
      if (line[i] == '|')
        break;
      fileCnic += line[i];
    }

    if (fileCnic == cnic)
      sessions.push_back(line);
  }
  file.close();
  return sessions;
}

vector<string> SessionsFileManager::loadAllSessions()
{
  vector<string> sessions;
  ifstream file(filePath);
  string line;

  while (getline(file, line))
  {
    if (!line.empty())
      sessions.push_back(line);
  }
  file.close();
  return sessions;
}