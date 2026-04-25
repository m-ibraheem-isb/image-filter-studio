#pragma once
#include <string>
using namespace std;

class User
{
private:
  string cnic;
  string password;
  string fullName;

public:
  User(string cnic, string password, string fullName);
  virtual ~User();

  virtual bool login() = 0;
  virtual void logout() = 0;

  string getCnic() const;
  string getPassword() const;
  string getFullName() const;
};