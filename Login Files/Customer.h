#pragma once
#include "User.h"
#include <string>
using namespace std;

class Customer : public User
{
private:
  string gender;
  string phone;
  string city;
  bool isBlocked;

public:
  Customer(string cnic, string password, string fullName,
           string gender, string phone, string city);

  bool login() override;
  void logout() override;

  void registerAccount();
  void loadImage(string path);
  void buildPipeline();
  void applyFilters();
  void viewSessionHistory();

  string getGender() const;
  string getPhone() const;
  string getCity() const;
  bool getIsBlocked() const;
  void setIsBlocked(bool status);
};