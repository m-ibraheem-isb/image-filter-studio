#include "CustomersFileManager.h"
#include <fstream>

CustomersFileManager::CustomersFileManager()
{
  customersFilePath = "customers.txt";
  blockedCnicsFilePath = "blocked_cnics.txt";
}

CustomersFileManager::CustomersFileManager(string path)
{
  customersFilePath = path;
  blockedCnicsFilePath = "blocked_cnics.txt";
}

void CustomersFileManager::registerCustomer(string cnic, string password,
                                           string name, string gender, string phone, string city)
{
  ofstream file(customersFilePath, ios::app);
  file << cnic << "|" << password << "|" << name << "|"
       << gender << "|" << phone << "|" << city << "|0" << endl;
  file.close();
}

string CustomersFileManager::findCustomer(string cnic)
{
  ifstream file(customersFilePath);
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
    {
      file.close();
      return line;
    }
  }
  file.close();
  return "";
}

void CustomersFileManager::blockCustomer(string cnic)
{
  vector<string> records = loadAllCustomers();
  ofstream file(customersFilePath);

  for (int i = 0; i < records.size(); i++)
  {
    string fileCnic = "";
    for (int j = 0; j < records[i].length(); j++)
    {
      if (records[i][j] == '|')
        break;
      fileCnic += records[i][j];
    }

    if (fileCnic == cnic)
    {
      string newLine = "";
      int barCount = 0;
      for (int j = 0; j < records[i].length(); j++)
      {
        if (records[i][j] == '|')
          barCount++;
        if (barCount == 6)
          break;
        newLine += records[i][j];
      }
      file << newLine << "|1" << endl;
    }
    else
    {
      file << records[i] << endl;
    }
  }
  file.close();

  ofstream blockedFile(blockedCnicsFilePath, ios::app);
  blockedFile << cnic << endl;
  blockedFile.close();
}

void CustomersFileManager::deleteCustomer(string cnic)
{
  vector<string> records = loadAllCustomers();
  ofstream file(customersFilePath);

  for (int i = 0; i < records.size(); i++)
  {
    string fileCnic = "";
    for (int j = 0; j < records[i].length(); j++)
    {
      if (records[i][j] == '|')
        break;
      fileCnic += records[i][j];
    }

    if (fileCnic != cnic)
      file << records[i] << endl;
  }
  file.close();
}

vector<string> CustomersFileManager::loadAllCustomers()
{
  vector<string> customers;
  ifstream file(customersFilePath);
  string line;

  while (getline(file, line))
  {
    if (!line.empty())
      customers.push_back(line);
  }
  file.close();
  return customers;
}

bool CustomersFileManager::isCnicBlocked(string cnic)
{
  ifstream file(blockedCnicsFilePath);
  string line;

  while (getline(file, line))
  {
    if (line == cnic)
    {
      file.close();
      return true;
    }
  }
  file.close();
  return false;
}

bool CustomersFileManager::validateLogin(string cnic, string password)
{
  string record = findCustomer(cnic);

  if (record.empty())
    return false;

  string parts[7];
  int partIndex = 0;
  string current = "";

  for (int i = 0; i < record.length(); i++)
  {
    if (record[i] == '|')
    {
      parts[partIndex] = current;
      partIndex++;
      current = "";
    }
    else
    {
      current += record[i];
    }
  }
  parts[partIndex] = current;

  if (parts[1] != password)
    return false;

  if (parts[6] == "1")
    return false;

  return true;
}