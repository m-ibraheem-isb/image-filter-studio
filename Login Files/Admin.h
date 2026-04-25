#pragma once
#include "User.h"
#include <string>
using namespace std;

class Admin : public User
{
public:
  Admin(string cnic, string password, string fullName);

  bool login() override;
  void logout() override;

  void manageFilterCatalogue();
  void viewAllSessions();
  void viewAllCustomers();
  string searchCustomer(string cnic);
  void blockCustomer(string cnic);
  void deleteCustomer(string cnic);
};