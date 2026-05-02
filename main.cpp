#include <iostream>
#include "Core/Pixel.h"
#include "Core/Image.h"
#include "Core/Catalouge.h"
#include "Login Files/Admin.h"
#include "Login Files/Customer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

using namespace std;

void showAdminMenu(Admin &admin)
{
  int choice;
  do
  {
    cout << "\n========================================" << endl;
    cout << "     ADMIN PANEL : Image Filter Studio  " << endl;
    cout << "========================================" << endl;
    cout << "  1. Manage Filter Catalog              " << endl;
    cout << "  2. Manage Customers                   " << endl;
    cout << "  3. View All Sessions                  " << endl;
    cout << "  4. Logout                             " << endl;
    cout << "========================================" << endl;
    cout << "Your choice: ";
    cin >> choice;

    if (choice == 1)
      admin.manageFilterCatalogue();
    else if (choice == 2)
    {
      int subChoice;
      cout << "\n1. View All Customers" << endl;
      cout << "2. Search Customer" << endl;
      cout << "3. Block Customer" << endl;
      cout << "4. Delete Customer" << endl;
      cout << "Enter choice: ";
      cin >> subChoice;

      if (subChoice == 1)
        admin.viewAllCustomers();
      else if (subChoice == 2)
      {
        string cnic;
        cout << "Enter CNIC to search: ";
        cin >> cnic;
        admin.searchCustomer(cnic);
      }
      else if (subChoice == 3)
      {
        string cnic;
        cout << "Enter CNIC to block: ";
        cin >> cnic;
        admin.blockCustomer(cnic);
      }
      else if (subChoice == 4)
      {
        string cnic;
        cout << "Enter CNIC to delete: ";
        cin >> cnic;
        admin.deleteCustomer(cnic);
      }
    }
    else if (choice == 3)
      admin.viewAllSessions();
    else if (choice == 4)
      admin.logout();

  } while (choice != 4);
}

void showCustomerMenu(Customer &customer)
{
  int choice;
  do
  {
    cout << "\n========================================" << endl;
    cout << "  Welcome, " << customer.getFullName() << endl;
    cout << "========================================" << endl;
    cout << "  1. Browse Filter Catalog              " << endl;
    cout << "  2. Load Image and Apply Filters       " << endl;
    cout << "  3. View My Session History            " << endl;
    cout << "  4. Logout                             " << endl;
    cout << "========================================" << endl;
    cout << "Your choice: ";
    cin >> choice;

    if (choice == 1)
      customer.buildPipeline();
    else if (choice == 2)
      customer.applyFilters();
    else if (choice == 3)
      customer.viewSessionHistory();
    else if (choice == 4)
      customer.logout();

  } while (choice != 4);
}

int main()
{
  int choice;
  do
  {
    cout << "\n========================================" << endl;
    cout << "        IMAGE FILTER STUDIO             " << endl;
    cout << "========================================" << endl;
    cout << "  1. Admin Login                        " << endl;
    cout << "  2. Customer Login                     " << endl;
    cout << "  3. New Customer? Register here        " << endl;
    cout << "  4. Exit                               " << endl;
    cout << "========================================" << endl;
    cout << "Your choice: ";
    cin >> choice;

    if (choice == 1)
    {
      Admin admin("0000000000000", "Admin1234", "Administrator");
      if (admin.login())
        showAdminMenu(admin);
    }
    else if (choice == 2)
    {
      Customer customer("", "", "", "", "", "");
      if (customer.login())
        showCustomerMenu(customer);
    }
    else if (choice == 3)
    {
      Customer customer("", "", "", "", "", "");
      customer.registerAccount();
    }
    else if (choice == 4)
    {
      cout << "Goodbye!" << endl;
    }

  } while (choice != 4);

  return 0;
}