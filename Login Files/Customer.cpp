#include "Customer.h"
#include "../Manager Files/CustomersFileManager.h"
#include "../Manager Files/SessionsFileManager.h"
#include "../Manager Files/ImageFileManager.h"
#include "../Core/Catalouge.h"
#include "../Core/FilterSession.h"
#include "../Filters/BrightnessFilter.h"
#include <iostream>
#include <limits>
#include <string>
#include <conio.h>
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

    if (cfm.isCnicBlocked(inputCnic))
    {
      cout << "This account is blocked. Contact admin." << endl;
      return false;
    }

    if (cfm.validateLogin(inputCnic, inputPass))
    {
      setCnic(inputCnic);
      string record = cfm.findCustomer(inputCnic);
      string parts[7];
      int pi = 0;
      string cur = "";
      for (char c : record)
      {
        if (c == '|')
        {
          parts[pi++] = cur;
          cur = "";
        }
        else if (c != '\r')
          cur += c;
      }
      parts[pi] = cur;
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
  bool allDigits = true;
  for (char c : cnic)
    if (c < '0' || c > '9')
    {
      allDigits = false;
      break;
    }
  if (!allDigits)
  {
    cout << "CNIC must contain digits only." << endl;
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

  cout << "Enter Password (exactly 9 chars, 1 uppercase, 1 digit): ";
  char ch;
  password = "";
  while ((ch = _getch()) != '\r')
  {
    if (ch == '\b' && !password.empty())
    {
      password.pop_back();
      cout << "\b \b";
    }
    else if (ch != '\b')
    {
      password += ch;
      cout << '*';
    }
  }
  cout << endl;

  if (password.length() != 9)
  {
    cout << "Password must be exactly 9 characters." << endl;
    return;
  }
  bool hasUpper = false, hasDigit = false;
  for (char c : password)
  {
    if (c >= 'A' && c <= 'Z')
      hasUpper = true;
    if (c >= '0' && c <= '9')
      hasDigit = true;
  }
  if (!hasUpper || !hasDigit)
  {
    cout << "Password must have at least 1 uppercase letter and 1 digit." << endl;
    return;
  }

  cout << "Confirm Password: ";
  char ch2;
  confirmPass = "";
  while ((ch2 = _getch()) != '\r')
  {
    if (ch2 == '\b' && !confirmPass.empty())
    {
      confirmPass.pop_back();
      cout << "\b \b";
    }
    else if (ch2 != '\b')
    {
      confirmPass += ch2;
      cout << '*';
    }
  }
  cout << endl;

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

void Customer::buildPipeline()
{
  Catalogue cat("Data/Catalouge.txt");
  cat.loadFilters();
  vector<Filter *> enabled = cat.getEnabledFilters();

  if (enabled.empty())
  {
    cout << "\nNo filters currently available." << endl;
    return;
  }

  int rows = enabled.size();
  string table[100][4];
  int w[4] = {2, 4, 8, 6};

  for (int i = 0; i < rows && i < 100; i++)
  {
    table[i][0] = to_string(enabled[i]->getFilterID());
    table[i][1] = enabled[i]->getFilterName();
    table[i][2] = enabled[i]->getCategory();
    table[i][3] = enabled[i]->isFilterEnabled() ? "Enabled" : "Disabled";

    for (int j = 0; j < 4; j++)
    {
      if ((int)table[i][j].length() > w[j])
        w[j] = table[i][j].length();
    }
  }

  cout << "\n╔";
  for (int i = 0; i < w[0] + 2; i++)
    cout << "═";
  cout << "╤";
  for (int i = 0; i < w[1] + 2; i++)
    cout << "═";
  cout << "╤";
  for (int i = 0; i < w[2] + 2; i++)
    cout << "═";
  cout << "╤";
  for (int i = 0; i < w[3] + 2; i++)
    cout << "═";
  cout << "╗\n";

  cout << "║ " << "ID";
  for (int i = 0; i < w[0] - 2; i++)
    cout << " ";
  cout << " │ ";
  cout << "Name";
  for (int i = 0; i < w[1] - 4; i++)
    cout << " ";
  cout << " │ ";
  cout << "Category";
  for (int i = 0; i < w[2] - 8; i++)
    cout << " ";
  cout << " │ ";
  cout << "Status";
  for (int i = 0; i < w[3] - 6; i++)
    cout << " ";
  cout << " ║\n";

  cout << "╠";
  for (int i = 0; i < w[0] + 2; i++)
    cout << "═";
  cout << "╪";
  for (int i = 0; i < w[1] + 2; i++)
    cout << "═";
  cout << "╪";
  for (int i = 0; i < w[2] + 2; i++)
    cout << "═";
  cout << "╪";
  for (int i = 0; i < w[3] + 2; i++)
    cout << "═";
  cout << "╣\n";

  for (int r = 0; r < rows && r < 100; r++)
  {
    cout << "║ " << table[r][0];
    for (int i = 0; i < w[0] - (int)table[r][0].length(); i++)
      cout << " ";
    cout << " │ ";
    cout << table[r][1];
    for (int i = 0; i < w[1] - (int)table[r][1].length(); i++)
      cout << " ";
    cout << " │ ";
    cout << table[r][2];
    for (int i = 0; i < w[2] - (int)table[r][2].length(); i++)
      cout << " ";
    cout << " │ ";
    cout << table[r][3];
    for (int i = 0; i < w[3] - (int)table[r][3].length(); i++)
      cout << " ";
    cout << " ║\n";
  }

  cout << "╚";
  for (int i = 0; i < w[0] + 2; i++)
    cout << "═";
  cout << "╧";
  for (int i = 0; i < w[1] + 2; i++)
    cout << "═";
  cout << "╧";
  for (int i = 0; i < w[2] + 2; i++)
    cout << "═";
  cout << "╧";
  for (int i = 0; i < w[3] + 2; i++)
    cout << "═";
  cout << "╝\n";
}

void Customer::applyFilters()
{
  cout << "\n=== Load Image ===" << endl;
  cout << "1. Load from JPG/PNG file" << endl;
  cout << "2. Generate test pattern (for testing without a real image)" << endl;
  cout << "Choice: ";
  int loadChoice;
  cin >> loadChoice;

  Image *imgPtr = nullptr;
  ImageFileManager ifm;

  if (loadChoice == 1)
  {
    string imagePath;
    cout << "Enter path to image file: ";
    cin >> imagePath;
    imgPtr = ifm.loadImage(imagePath);
    if (imgPtr == nullptr)
    {
      cout << "Failed to load image. Check path and try again." << endl;
      return;
    }
    cout << "Image loaded: " << imgPtr->getWidth() << " x "
         << imgPtr->getHeight() << " pixels ("
         << (imgPtr->getWidth() * imgPtr->getHeight()) << " pixels total)" << endl;
  }
  else
  {
    int tw = 80, th = 40;
    imgPtr = new Image(th, tw);
    for (int r = 0; r < th; r++)
      for (int c = 0; c < tw; c++)
      {
        imgPtr->at(r, c).setR((r * 255) / th);
        imgPtr->at(r, c).setG((c * 255) / tw);
        imgPtr->at(r, c).setB(128);
      }
    cout << "Test pattern generated: " << tw << " x " << th << endl;
  }

  imgPtr->displayASCII();
  cout << "Image ready. Now build your filter pipeline." << endl;

  Catalogue cat("Data/Catalouge.txt");
  cat.loadFilters();
  vector<Filter *> allFilters = cat.getAllFilters();

  FilterSession session(getCnic(), imgPtr);

  cout << "\n=== Build Filter Pipeline ===" << endl;
  session.displayPipeline();

  cout << "\nAvailable Filters:" << endl;
  for (int i = 0; i < (int)allFilters.size(); i++)
  {
    string status = allFilters[i]->isFilterEnabled() ? "Enabled" : "Disabled";
    cout << "  " << allFilters[i]->getFilterID() << "  "
         << allFilters[i]->getFilterName()
         << " [" << allFilters[i]->getCategory() << "]  " << status << endl;
  }

  int id;
  cout << "\nEnter filter ID to add (0 to finish): ";
  cin >> id;

  while (id != 0)
  {
    Filter *f = cat.findFilter(id);
    if (f == nullptr)
    {
      cout << "Filter not found." << endl;
    }
    else if (!f->isFilterEnabled())
    {
      cout << "Filter '" << f->getFilterName() << "' is disabled by Admin." << endl;
    }
    else
    {
      if (f->getFilterID() == 3)
      {
        int amount;
        cout << "Enter brightness amount (-100 to +100): ";
        cin >> amount;
        if (amount < -100)
          amount = -100;
        if (amount > 100)
          amount = 100;
        f = new BrightnessFilter(amount);
        f->setEnabled(true);
        session.addFilter(f);
        cout << "Added: Brightness Adjust (" << (amount >= 0 ? "+" : "") << amount << ")" << endl;
      }
      else
      {
        session.addFilter(f);
        cout << "Added: " << f->getFilterName() << endl;
      }
      session.displayPipeline();
    }
    cout << "Enter filter ID to add (0 to finish): ";
    cin >> id;
  }

  cout << "\nPipeline finalised." << endl;
  session.applyAll();

  char save;
  cout << "\nSave result? (y/n): ";
  cin >> save;
  if (save == 'y' || save == 'Y')
  {
    string outFile = session.generateOutputFileName();
    session.saveResult("");
    cout << "\nOpen the file in any image viewer to see your result." << endl;
    cout << "Session recorded in Data/Sesssions.txt." << endl;
  }

  delete imgPtr;
}

void Customer::viewSessionHistory()
{
  SessionsFileManager sfm("Data/Sesssions.txt");
  vector<string> sessions = sfm.loadCustomerSessions(getCnic());

  if (sessions.empty())
  {
    cout << "\nNo sessions found." << endl;
    return;
  }

  int rows = sessions.size();
  string table[100][4];
  int w[4] = {4, 9, 15, 11};

  for (int i = 0; i < rows && i < 100; i++)
  {
    string line = sessions[i];
    string parts[4] = {"", "", "", ""};
    int partIdx = 0;

    for (char c : line)
    {
      if (c == '|')
      {
        if (partIdx < 3)
          partIdx++;
      }
      else if (c != '\r')
      {
        parts[partIdx] += c;
      }
    }

    for (int j = 0; j < 4; j++)
    {
      table[i][j] = parts[j];
      int len = table[i][j].length();
      if (len > w[j])
      {
        if (j == 2 && len > 35)
          w[j] = 35;
        else if (j == 3 && len > 32)
          w[j] = 32;
        else
          w[j] = len;
      }
    }
  }

  cout << "\n╔";
  for (int i = 0; i < w[0] + 2; i++)
    cout << "═";
  cout << "╤";
  for (int i = 0; i < w[1] + 2; i++)
    cout << "═";
  cout << "╤";
  for (int i = 0; i < w[2] + 2; i++)
    cout << "═";
  cout << "╤";
  for (int i = 0; i < w[3] + 2; i++)
    cout << "═";
  cout << "╗\n";

  cout << "║ " << "CNIC";
  for (int i = 0; i < w[0] - 4; i++)
    cout << " ";
  cout << " │ ";
  cout << "Timestamp";
  for (int i = 0; i < w[1] - 9; i++)
    cout << " ";
  cout << " │ ";
  cout << "Filters Applied";
  for (int i = 0; i < w[2] - 15; i++)
    cout << " ";
  cout << " │ ";
  cout << "Output File";
  for (int i = 0; i < w[3] - 11; i++)
    cout << " ";
  cout << " ║\n";

  cout << "╠";
  for (int i = 0; i < w[0] + 2; i++)
    cout << "═";
  cout << "╪";
  for (int i = 0; i < w[1] + 2; i++)
    cout << "═";
  cout << "╪";
  for (int i = 0; i < w[2] + 2; i++)
    cout << "═";
  cout << "╪";
  for (int i = 0; i < w[3] + 2; i++)
    cout << "═";
  cout << "╣\n";

  for (int r = 0; r < rows && r < 100; r++)
  {
    cout << "║ ";
    for (int j = 0; j < 4; j++)
    {
      string cell = table[r][j];
      if ((int)cell.length() > w[j])
        cout << cell.substr(0, w[j]);
      else
      {
        cout << cell;
        for (int k = 0; k < w[j] - (int)cell.length(); k++)
          cout << " ";
      }
      if (j < 3)
        cout << " │ ";
    }
    cout << " ║\n";
  }

  cout << "╚";
  for (int i = 0; i < w[0] + 2; i++)
    cout << "═";
  cout << "╧";
  for (int i = 0; i < w[1] + 2; i++)
    cout << "═";
  cout << "╧";
  for (int i = 0; i < w[2] + 2; i++)
    cout << "═";
  cout << "╧";
  for (int i = 0; i < w[3] + 2; i++)
    cout << "═";
  cout << "╝\n";
}

string Customer::getGender() const { return gender; }
string Customer::getPhone() const { return phone; }
string Customer::getCity() const { return city; }
bool Customer::getIsBlocked() const { return isBlocked; }
void Customer::setIsBlocked(bool status) { isBlocked = status; }