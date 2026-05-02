#include "Admin.h"
#include "../Manager Files/CustomersFileManager.h"
#include "../Manager Files/SessionsFileManager.h"
#include "../Core/Catalouge.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

static void tblLine(const int cols[], int n, const string &l, const string &m, const string &j, const string &r)
{
  cout << l;
  for (int i = 0; i < n; i++)
  {
    for (int k = 0; k < cols[i]; k++)
      cout << m;
    cout << (i < n - 1 ? j : r);
  }
  cout << "\n";
}

static void tblRow(const string cells[], const int cols[], int n)
{
  cout << "║";
  for (int i = 0; i < n; i++)
  {
    string val = " " + cells[i];
    if ((int)val.length() > cols[i] - 1)
      val = val.substr(0, cols[i] - 1);
    cout << left << setw(cols[i]) << val << "║";
  }
  cout << "\n";
}

Admin::Admin(string cnic, string password, string fullName)
    : User(cnic, password, fullName) {}

bool Admin::login()
{
  const string ADMIN_CNIC = "0000000000000";
  const string ADMIN_PASS = "Admin1234";
  string inputCnic, inputPass;
  cout << "Enter Admin CNIC: ";
  cin >> inputCnic;

  cout << "Enter Admin Password: ";
  char ch;
  inputPass = "";
  while ((ch = _getch()) != '\r')
  {
    if (ch == '\b' && !inputPass.empty())
    {
      inputPass.pop_back();
      cout << "\b \b";
    }
    else if (ch != '\b')
    {
      inputPass += ch;
      cout << '*';
    }
  }
  cout << endl;

  if (inputCnic == ADMIN_CNIC && inputPass == ADMIN_PASS)
  {
    cout << "Admin login successful." << endl;
    return true;
  }
  cout << "Invalid admin credentials." << endl;
  return false;
}

void Admin::logout()
{
  cout << "Admin logged out." << endl;
}

void Admin::manageFilterCatalogue()
{
  Catalogue cat("Data/Catalouge.txt");
  cat.loadFilters();
  int choice;

  cout << "\n╔══════════════════════════════════════════════╗\n";
  cout << "║       Manage Filter Catalogue                ║\n";
  cout << "╠══════════════════════════════════════════════╣\n";
  cout << "║  1. View All Filters                         ║\n";
  cout << "║  2. Enable a Filter                          ║\n";
  cout << "║  3. Disable a Filter                         ║\n";
  cout << "╚══════════════════════════════════════════════╝\n";
  cout << "Enter choice: ";
  cin >> choice;

  if (choice == 1)
  {
    vector<Filter *> filters = cat.getAllFilters();
    int cols[] = {5, 24, 20, 11};
    int n = 4;
    cout << "\n";
    tblLine(cols, n, "╔", "═", "╦", "╗");
    string hdr[] = {"ID", "Name", "Category", "Status"};
    tblRow(hdr, cols, n);
    tblLine(cols, n, "╠", "═", "╬", "╣");
    for (int i = 0; i < (int)filters.size(); i++)
    {
      string status = filters[i]->isFilterEnabled() ? "Enabled" : "Disabled";
      string row[] = {
          to_string(filters[i]->getFilterID()),
          filters[i]->getFilterName(),
          filters[i]->getCategory(),
          status};
      tblRow(row, cols, n);
    }
    tblLine(cols, n, "╚", "═", "╩", "╝");
  }
  else if (choice == 2)
  {
    int id;
    cout << "Enter filter ID to enable: ";
    cin >> id;
    cat.enableFilter(id);
    cout << "Filter enabled and saved." << endl;
  }
  else if (choice == 3)
  {
    int id;
    cout << "Enter filter ID to disable: ";
    cin >> id;
    cat.disableFilter(id);
    cout << "Filter disabled and saved." << endl;
  }
}

void Admin::viewAllSessions()
{
  SessionsFileManager sfm("Data/Sesssions.txt");
  vector<string> sessions = sfm.loadAllSessions();

  int cols[] = {15, 18, 30, 34};
  int n = 4;
  cout << "\n";
  tblLine(cols, n, "╔", "═", "╦", "╗");
  string hdr[] = {"CNIC", "Timestamp", "Filters Applied", "Output File"};
  tblRow(hdr, cols, n);
  tblLine(cols, n, "╠", "═", "╬", "╣");

  if (sessions.empty())
  {
    cout << "║ No sessions recorded yet.\n";
  }
  for (int i = 0; i < (int)sessions.size(); i++)
  {
    string line = sessions[i];
    if (!line.empty() && line.back() == '\r')
      line.pop_back();
    string parts[4] = {"", "", "", ""};
    int pi = 0;
    for (int j = 0; j < (int)line.length(); j++)
    {
      if (line[j] == '|')
      {
        if (pi < 3)
          pi++;
      }
      else
        parts[pi] += line[j];
    }
    tblRow(parts, cols, n);
  }
  tblLine(cols, n, "╚", "═", "╩", "╝");
}

void Admin::viewAllCustomers()
{
  CustomersFileManager cfm;
  vector<string> customers = cfm.loadAllCustomers();

  int cols[] = {15, 20, 8, 14, 14, 9};
  int n = 6;
  cout << "\n";
  tblLine(cols, n, "╔", "═", "╦", "╗");
  string hdr[] = {"CNIC", "Name", "Gender", "Phone", "City", "Status"};
  tblRow(hdr, cols, n);
  tblLine(cols, n, "╠", "═", "╬", "╣");

  if (customers.empty())
  {
    cout << "║ No customers registered.\n";
  }
  for (int i = 0; i < (int)customers.size(); i++)
  {
    string line = customers[i];
    if (!line.empty() && line.back() == '\r')
      line.pop_back();
    string parts[7] = {"", "", "", "", "", "", ""};
    int pi = 0;
    for (int j = 0; j < (int)line.length(); j++)
    {
      if (line[j] == '|')
      {
        if (pi < 6)
          pi++;
      }
      else
        parts[pi] += line[j];
    }
    string status = (parts[6] == "1") ? "Blocked" : "Active";
    string row[] = {parts[0], parts[2], parts[3], parts[4], parts[5], status};
    tblRow(row, cols, n);
  }
  tblLine(cols, n, "╚", "═", "╩", "╝");
}

string Admin::searchCustomer(string cnic)
{
  CustomersFileManager cfm;
  string record = cfm.findCustomer(cnic);
  if (record.empty())
  {
    cout << "Customer not found." << endl;
    return record;
  }
  if (!record.empty() && record.back() == '\r')
    record.pop_back();
  string parts[7] = {"", "", "", "", "", "", ""};
  int pi = 0;
  for (int j = 0; j < (int)record.length(); j++)
  {
    if (record[j] == '|')
    {
      if (pi < 6)
        pi++;
    }
    else
      parts[pi] += record[j];
  }
  string status = (parts[6] == "1") ? "Blocked" : "Active";

  cout << "\n╔══════════════════════════════════════╗\n";
  cout << "║          Customer Details            ║\n";
  cout << "╠══════════════════════════════════════╣\n";
  cout << "║  CNIC   : " << left << setw(26) << parts[0] << "║\n";
  cout << "║  Name   : " << left << setw(26) << parts[2] << "║\n";
  cout << "║  Gender : " << left << setw(26) << parts[3] << "║\n";
  cout << "║  Phone  : " << left << setw(26) << parts[4] << "║\n";
  cout << "║  City   : " << left << setw(26) << parts[5] << "║\n";
  cout << "║  Status : " << left << setw(26) << status << "║\n";
  cout << "╚══════════════════════════════════════╝\n";
  return record;
}

void Admin::blockCustomer(string cnic)
{
  CustomersFileManager cfm;
  if (cfm.findCustomer(cnic).empty())
  {
    cout << "Customer not found." << endl;
    return;
  }
  cfm.blockCustomer(cnic);
  cout << "Customer blocked successfully." << endl;
}

void Admin::unblockCustomer(string cnic)
{
  CustomersFileManager cfm;
  if (cfm.findCustomer(cnic).empty())
  {
    cout << "Customer not found." << endl;
    return;
  }
  cfm.unblockCustomer(cnic);
  cout << "Customer unblocked successfully." << endl;
}

void Admin::deleteCustomer(string cnic)
{
  CustomersFileManager cfm;
  if (cfm.findCustomer(cnic).empty())
  {
    cout << "Customer not found." << endl;
    return;
  }
  cfm.deleteCustomer(cnic);
  cout << "Customer deleted successfully." << endl;
}