#include "Admin.h"
#include "../Manager Files/CustomersFileManager.h"
#include "../Manager Files/SessionsFileManager.h"
#include "../Core/Catalouge.h"
#include <iostream>
using namespace std;

Admin::Admin(string cnic, string password, string fullName)
    : User(cnic, password, fullName)
{
}

bool Admin::login()
{
  string adminCnic = "0000000000000";
  string adminPass = "Admin1234";
  string inputCnic, inputPass;

  cout << "Enter Admin CNIC: ";
  cin >> inputCnic;
  cout << "Enter Admin Password: ";
  cin >> inputPass;

  if (inputCnic == adminCnic && inputPass == adminPass)
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
  Catalogue cat("catalog.txt");
  cat.loadFilters();
  int choice;

  cout << "\n=== Manage Filter Catalogue ===" << endl;
  cout << "1. View All Filters" << endl;
  cout << "2. Enable Filter" << endl;
  cout << "3. Disable Filter" << endl;
  cout << "Enter choice: ";
  cin >> choice;

  if (choice == 1)
  {
    vector<Filter *> filters = cat.getAllFilters();
    for (int i = 0; i < filters.size(); i++)
    {
      cout << filters[i]->getFilterID() << " | "
           << filters[i]->getFilterName() << " | "
           << (filters[i]->isFilterEnabled() ? "Enabled" : "Disabled")
           << endl;
    }
  }
  else if (choice == 2)
  {
    int id;
    cout << "Enter filter ID to enable: ";
    cin >> id;
    cat.enableFilter(id);
    cout << "Filter enabled." << endl;
  }
  else if (choice == 3)
  {
    int id;
    cout << "Enter filter ID to disable: ";
    cin >> id;
    cat.disableFilter(id);
    cout << "Filter disabled." << endl;
  }
}

void Admin::viewAllSessions()
{
  SessionsFileManager sfm("Data/Sessions.txt");
  vector<string> sessions = sfm.loadAllSessions();

  cout << "\n=== All Sessions ===" << endl;
  if (sessions.empty())
  {
    cout << "No sessions found." << endl;
    return;
  }
  for (int i = 0; i < sessions.size(); i++)
    cout << sessions[i] << endl;
}

void Admin::viewAllCustomers()
{
  CustomersFileManager cfm;
  vector<string> customers = cfm.loadAllCustomers();

  cout << "\n=== All Customers ===" << endl;
  if (customers.empty())
  {
    cout << "No customers found." << endl;
    return;
  }
  for (int i = 0; i < customers.size(); i++)
    cout << customers[i] << endl;
}

string Admin::searchCustomer(string cnic)
{
  CustomersFileManager cfm;
  string record = cfm.findCustomer(cnic);
  if (record.empty())
    cout << "Customer not found." << endl;
  else
    cout << record << endl;
  return record;
}

void Admin::blockCustomer(string cnic)
{
  CustomersFileManager cfm;
  cfm.blockCustomer(cnic);
  cout << "Customer blocked successfully." << endl;
}

void Admin::deleteCustomer(string cnic)
{
  CustomersFileManager cfm;
  cfm.deleteCustomer(cnic);
  cout << "Customer deleted successfully." << endl;
}