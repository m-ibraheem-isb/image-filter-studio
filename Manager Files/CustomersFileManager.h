#pragma once
#include <vector>
#include <string>
using namespace std;

class CustomersFileManager
{
private:
  string customersFilePath;
  string blockedCnicsFilePath;

public:
  CustomersFileManager();
  CustomersFileManager(string path);

  void registerCustomer(string cnic, string password,
                        string name, string gender,
                        string phone, string city);
  string findCustomer(string cnic);
  void blockCustomer(string cnic);
  void unblockCustomer(string cnic);
  void deleteCustomer(string cnic);
  vector<string> loadAllCustomers();
  bool isCnicBlocked(string cnic);
  bool validateLogin(string cnic, string password);
};