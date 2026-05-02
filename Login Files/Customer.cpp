#include "Customer.h"
#include "../Manager Files/CustomersFileManager.h"
#include "../Manager Files/SessionsFileManager.h"
#include "../Manager Files/ImageFileManager.h"
#include "../Core/Catalouge.h"
#include "../Core/FilterSession.h"
#include <iostream>
using namespace std;

Customer::Customer(string cnic, string password, string fullName,
                   string gender, string phone, string city)
    : User(cnic, password, fullName)
{
  this->gender = gender;
  this->phone = phone;
  this->city = city;
  this->isBlocked = false;
}

bool Customer::login()
{
  CustomersFileManager cfm;
  string inputCnic, inputPass;
  int attempts = 0;

  while (attempts < 3)
  {
    cout << "Enter CNIC: ";
    cin >> inputCnic;
    cout << "Enter Password: ";
    cin >> inputPass;

    if (cfm.isCnicBlocked(inputCnic))
    {
      cout << "This account is blocked. Contact admin." << endl;
      return false;
    }

    if (cfm.validateLogin(inputCnic, inputPass))
    {
      // Store CNIC and name into this object
      setCnic(inputCnic);

      // Get full name from record
      string record = cfm.findCustomer(inputCnic);
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
        else if (record[i] != '\r')
        {
          current += record[i];
        }
      }
      parts[partIndex] = current;
      setFullName(parts[2]);

      cout << "Login successful. Welcome, " << getFullName() << "!" << endl;
      return true;
    }

    attempts++;
    cout << "Invalid credentials. Attempts left: " << (3 - attempts) << endl;
  }

  cout << "Too many failed attempts. Returning to main menu." << endl;
  return false;
}

void Customer::logout()
{
  cout << "Customer logged out." << endl;
}

void Customer::registerAccount()
{
  CustomersFileManager cfm;
  string cnic, password, confirmPass, name, gender, phone, city;

  cout << "Enter CNIC (13 digits): ";
  cin >> cnic;

  if (cnic.length() != 13)
  {
    cout << "Invalid CNIC. Must be exactly 13 digits." << endl;
    return;
  }

  if (cfm.isCnicBlocked(cnic))
  {
    cout << "This CNIC is blocked. Cannot register." << endl;
    return;
  }

  if (!cfm.findCustomer(cnic).empty())
  {
    cout << "CNIC already registered." << endl;
    return;
  }

  cout << "Enter Password (9 chars, 1 uppercase, 1 digit): ";
  cin >> password;

  if (password.length() < 9)
  {
    cout << "Password must be exactly 9 characters." << endl;
    return;
  }

  bool hasUpper = false;
  bool hasDigit = false;
  for (int i = 0; i < password.length(); i++)
  {
    if (password[i] >= 'A' && password[i] <= 'Z')
      hasUpper = true;
    if (password[i] >= '0' && password[i] <= '9')
      hasDigit = true;
  }

  if (!hasUpper || !hasDigit)
  {
    cout << "Password must have at least 1 uppercase and 1 digit." << endl;
    return;
  }

  cout << "Confirm Password: ";
  cin >> confirmPass;

  if (password != confirmPass)
  {
    cout << "Passwords do not match." << endl;
    return;
  }

  cout << "Enter Full Name: ";
  cin.ignore();
  getline(cin, name);

  cout << "Enter Gender (M/F/Other): ";
  cin >> gender;

  cout << "Enter Phone: ";
  cin >> phone;

  cout << "Enter City: ";
  cin >> city;

  cfm.registerCustomer(cnic, password, name, gender, phone, city);
  cout << "Registration successful!" << endl;
}

void Customer::loadImage(string path)
{
  ImageFileManager ifm;
  Image *img = ifm.loadImage(path);
  if (img == nullptr)
  {
    cout << "Failed to load image. File not found." << endl;
    return;
  }
  cout << "Image loaded: " << img->getWidth() << " x " << img->getHeight() << endl;
  img->displayASCII();
  delete img;
}

void Customer::buildPipeline()
{
  Catalogue cat("Data/Catalouge.txt");
  cat.loadFilters();
  vector<Filter *> enabled = cat.getEnabledFilters();

  cout << "\n=== Available Filters ===" << endl;
  for (int i = 0; i < enabled.size(); i++)
  {
    cout << enabled[i]->getFilterID() << ". "
         << enabled[i]->getFilterName() << " ["
         << enabled[i]->getCategory() << "]" << endl;
  }
}

void Customer::applyFilters()
{
  string imagePath;
  cout << "Enter image path: ";
  cin >> imagePath;

  ImageFileManager ifm;
  Image *imgPtr = ifm.loadImage(imagePath);

  if (imgPtr == nullptr)
  {
    cout << "Failed to load image. Check path and try again." << endl;
    return;
  }

  cout << "Image loaded: " << imgPtr->getWidth() << " x " << imgPtr->getHeight() << endl;

  FilterSession session(getCnic(), imgPtr);

  Catalogue cat("Data/Catalouge.txt");
  cat.loadFilters();
  vector<Filter *> enabled = cat.getEnabledFilters();

  cout << "\n=== Available Filters ===" << endl;
  for (int i = 0; i < enabled.size(); i++)
  {
    cout << enabled[i]->getFilterID() << ". "
         << enabled[i]->getFilterName() << endl;
  }

  int id;
  cout << "Enter filter ID to add (0 to finish): ";
  cin >> id;

  while (id != 0)
  {
    Filter *f = cat.findFilter(id);
    if (f != nullptr)
    {
      session.addFilter(f);
      cout << "Added: " << f->getFilterName() << endl;
      session.displayPipeline();
    }
    else
      cout << "Filter not found." << endl;

    cout << "Enter filter ID to add (0 to finish): ";
    cin >> id;
  }

  cout << "\n=== Applying Pipeline ===" << endl;
  session.applyAll();

  char save;
  cout << "Save result? (y/n): ";
  cin >> save;

  if (save == 'y' || save == 'Y')
  {
    session.saveResult("");
    cout << "Image saved successfully." << endl;
    cout << "Session recorded." << endl;
  }

  delete imgPtr;
}

void Customer::viewSessionHistory()
{
  SessionsFileManager sfm("Data/Sessions.txt");
  vector<string> sessions = sfm.loadCustomerSessions(getCnic());

  cout << "\n=== Your Session History ===" << endl;
  if (sessions.empty())
  {
    cout << "No sessions found." << endl;
    return;
  }
  for (int i = 0; i < sessions.size(); i++)
    cout << sessions[i] << endl;
}

string Customer::getGender() const { return gender; }
string Customer::getPhone() const { return phone; }
string Customer::getCity() const { return city; }
bool Customer::getIsBlocked() const { return isBlocked; }
void Customer::setIsBlocked(bool status) { isBlocked = status; }