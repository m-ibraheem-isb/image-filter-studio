#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdlib>
#include <string>
#include "Core/Pixel.h"
#include "Core/Image.h"
#include "Core/Catalouge.h"
#include "Login Files/Admin.h"
#include "Login Files/Customer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

    using namespace std;

static void printMenuBox(const string &title, const string rows[], int rowCount, int w = 46)
{
  int maxNeededWidth = title.length() + 4;
  for (int i = 0; i < rowCount; i++)
  {
    int currentLen = 0;
    for (int j = 0; j < rows[i].length(); j++)
    {
      if (rows[i][j] == '\t')
        currentLen += 4;
      else
        currentLen++;
    }
    if (currentLen + 4 > maxNeededWidth)
      maxNeededWidth = currentLen + 4;
  }

  if (w < maxNeededWidth)
    w = maxNeededWidth;

  string topBar = "╔";
  string midBar = "╠";
  string botBar = "╚";
  string fill = "═";
  for (int i = 0; i < w; i++)
  {
    topBar += fill;
    midBar += fill;
    botBar += fill;
  }
  topBar += "╗";
  midBar += "╣";
  botBar += "╝";

  cout << "\n"
       << topBar << "\n";

  int pad = w - (int)title.length();
  int lp = pad / 2, rp = pad - lp;
  cout << "║";
  for (int i = 0; i < lp; i++)
    cout << " ";
  cout << title;
  for (int i = 0; i < rp; i++)
    cout << " ";
  cout << "║\n";

  cout << midBar << "\n";

  for (int i = 0; i < rowCount; i++)
  {
    string cleanRow = "";
    for (int j = 0; j < rows[i].length(); j++)
    {
      if (rows[i][j] == '\t')
        cleanRow += "    ";
      else
        cleanRow += rows[i][j];
    }
    int spaces = w - 2 - (int)cleanRow.length();
    if (spaces < 0)
      spaces = 0;
    cout << "║  " << cleanRow;
    for (int j = 0; j < spaces; j++)
      cout << " ";
    cout << "║\n";
  }
  cout << botBar << "\n";
}

void showAdminMenu(Admin &admin)
{
  int choice;
  do
  {
    system("cls");
    string rows[] = {
        "1. Manage Filter Catalog",
        "2. Manage Customers",
        "3. View All Sessions",
        "4. Logout"};
    printMenuBox("ADMIN PANEL : Image Filter Studio", rows, 4);
    cout << "Your choice: ";
    cin >> choice;

    if (choice == 1)
    {
      system("cls");
      admin.manageFilterCatalogue();
      cout << "\nPress Enter to return to Admin Panel...";
      cin.ignore();
      cin.get();
    }
    else if (choice == 2)
    {
      system("cls");
      string subRows[] = {
          "1. View All Customers",
          "2. Search Customer",
          "3. Block Customer",
          "4. Unblock Customer",
          "5. Delete Customer"};
      printMenuBox("Manage Customers", subRows, 5);
      cout << "Enter choice: ";
      int subChoice;
      cin >> subChoice;

      if (subChoice == 1)
      {
        system("cls");
        admin.viewAllCustomers();
        cout << "\nPress Enter to return to Admin Panel...";
        cin.ignore();
        cin.get();
      }
      else if (subChoice == 2)
      {
        system("cls");
        string cnic;
        cout << "Enter CNIC to search: ";
        cin >> cnic;
        admin.searchCustomer(cnic);
        cout << "\nPress Enter to return to Admin Panel...";
        cin.ignore();
        cin.get();
      }
      else if (subChoice == 3)
      {
        system("cls");
        string cnic;
        cout << "Enter CNIC to block: ";
        cin >> cnic;
        admin.blockCustomer(cnic);
        cout << "\nPress Enter to return to Admin Panel...";
        cin.ignore();
        cin.get();
      }
      else if (subChoice == 4)
      {
        system("cls");
        string cnic;
        cout << "Enter CNIC to unblock: ";
        cin >> cnic;
        admin.unblockCustomer(cnic);
        cout << "\nPress Enter to return to Admin Panel...";
        cin.ignore();
        cin.get();
      }
      else if (subChoice == 5)
      {
        system("cls");
        string cnic;
        cout << "Enter CNIC to delete: ";
        cin >> cnic;
        admin.deleteCustomer(cnic);
        cout << "\nPress Enter to return to Admin Panel...";
        cin.ignore();
        cin.get();
      }
    }
    else if (choice == 3)
    {
      system("cls");
      admin.viewAllSessions();
      cout << "\nPress Enter to return to Admin Panel...";
      cin.ignore();
      cin.get();
    }
    else if (choice == 4)
    {
      system("cls");
      admin.logout();
    }
  } while (choice != 4);
}

void showCustomerMenu(Customer &customer)
{
  int choice;
  do
  {
    system("cls");
    string welcomeRow = "Welcome, " + customer.getFullName();
    string rows[] = {
        welcomeRow,
        "1. Browse Filter Catalog",
        "2. Load Image and Apply Filters",
        "3. View My Session History",
        "4. Logout"};
    printMenuBox("IMAGE FILTER STUDIO", rows, 5);
    cout << "Your choice: ";
    cin >> choice;

    if (choice == 1)
    {
      system("cls");
      customer.buildPipeline();
      cout << "\nPress Enter to return to Customer Panel...";
      cin.ignore();
      cin.get();
    }
    else if (choice == 2)
    {
      system("cls");
      customer.applyFilters();
      cout << "\nPress Enter to return to Customer Panel...";
      cin.ignore();
      cin.get();
    }
    else if (choice == 3)
    {
      system("cls");
      customer.viewSessionHistory();
      cout << "\nPress Enter to return to Customer Panel...";
      cin.ignore();
      cin.get();
    }
    else if (choice == 4)
    {
      system("cls");
      customer.logout();
    }
  } while (choice != 4);
}

int main()
{
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif
  int choice;
  do
  {
    system("cls");
    string rows[] = {
        "1. Admin Login",
        "2. Customer Login",
        "3. New Customer? Register here",
        "4. Exit"};
    printMenuBox("IMAGE FILTER STUDIO", rows, 4);
    cout << "Your choice: ";
    cin >> choice;

    if (choice == 1)
    {
      system("cls");
      Admin admin("0000000000000", "Admin1234", "Administrator");
      if (admin.login())
        showAdminMenu(admin);
    }
    else if (choice == 2)
    {
      system("cls");
      Customer customer("", "", "", "", "", "");
      if (customer.login())
        showCustomerMenu(customer);
    }
    else if (choice == 3)
    {
      system("cls");
      Customer customer("", "", "", "", "", "");
      customer.registerAccount();
      cout << "\nPress Enter to return to main menu...";
      cin.ignore();
      cin.get();
    }
    else if (choice == 4)
    {
      system("cls");
      cout << "Goodbye!" << endl;
    }
  } while (choice != 4);

  return 0;
}