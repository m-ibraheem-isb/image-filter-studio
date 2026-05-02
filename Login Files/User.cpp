#include "User.h"
#include <iostream>
using namespace std;

User::User(string cnic, string password, string fullName)
{
  this->cnic = cnic;
  this->password = password;
  this->fullName = fullName;
  cout << "User created: " << fullName << endl;
}

User::~User()
{
  cout << "User destroyed: " << fullName << endl;
}
void User::setCnic(string c) { cnic = c; }
void User::setFullName(string n) { fullName = n; }
string User::getCnic() const { return cnic; }
string User::getPassword() const { return password; }
string User::getFullName() const { return fullName; }