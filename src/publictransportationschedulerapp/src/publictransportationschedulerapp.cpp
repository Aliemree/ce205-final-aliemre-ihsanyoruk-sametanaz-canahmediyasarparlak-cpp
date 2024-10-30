#include "publictransportationschedulerapp.h"
#include "publictransportationscheduler.h"
#include <iostream>

using namespace Coruh::PublicTransportationScheduler;

void showMainMenu() {
  int choice;

  while (true) {
    std::cout << "\n=== Main Menu ===\n";
    std::cout << "1. User Authentication\n";
    std::cout << "2. Band and Artist Management\n";
    std::cout << "3. Scheduling Performances\n";
    std::cout << "4. Ticket Sales Tracking\n";
    std::cout << "5. Vendor and Sponsor Coordination\n";
    std::cout << "0. Exit\n";
    std::cout << "Select an option: ";
    std::cin >> choice;

    switch (choice) {
      case 1:
        showUserAuthenticationMenu();
        break;

      case 2:
        showBandManagementMenu();
        break;

      case 3:
        showSchedulingMenu();
        break;

      case 4:
        showTicketSalesMenu();
        break;

      case 5:
        showVendorSponsorMenu();
        break;

      case 0:
        std::cout << "Exiting the application.\n";
        return;

      default:
        std::cout << "Invalid choice. Please try again.\n";
        break;
    }
  }
}

void showUserAuthenticationMenu() {
  int choice;

  while (true) {
    std::cout << "\n=== User Authentication ===\n";
    std::cout << "1. Login\n";
    std::cout << "2. Register\n";
    std::cout << "3. Guest Mode\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "Select an option: ";
    std::cin >> choice;
    std::string username, password;

    switch (choice) {
      case 1:
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        if (!PublicTransportationScheduler::login(username, password)) {
          std::cout << "Login failed.\n";
        }

        break;

      case 2:
        std::cout << "Enter new username: ";
        std::cin >> username;
        std::cout << "Enter new password: ";
        std::cin >> password;
        PublicTransportationScheduler::registerUser(username, password);
        break;

      case 3:
        std::cout << "Entering guest mode...\n";
        break;

      case 0:
        return;

      default:
        std::cout << "Invalid choice. Please try again.\n";
        break;
    }
  }
}

void showBandManagementMenu() {
  int choice;

  while (true) {
    std::cout << "\n=== Band and Artist Management ===\n";
    std::cout << "1. Add Band/Artist\n";
    std::cout << "2. Edit Band/Artist\n";
    std::cout << "3. View Band/Artist List\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "Select an option: ";
    std::cin >> choice;

    switch (choice) {
      case 1:
        std::cout << "Adding band/artist...\n";
        break;

      case 2:
        std::cout << "Editing band/artist...\n";
        break;

      case 3:
        std::cout << "Viewing band/artist list...\n";
        break;

      case 0:
        return;

      default:
        std::cout << "Invalid choice. Please try again.\n";
        break;
    }
  }
}

void showSchedulingMenu() {
  int choice;

  while (true) {
    std::cout << "\n=== Scheduling Performances ===\n";
    std::cout << "1. Create Schedule\n";
    std::cout << "2. Edit Schedule\n";
    std::cout << "3. View Festival Lineup\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "Select an option: ";
    std::cin >> choice;

    switch (choice) {
      case 1:
        std::cout << "Creating schedule...\n";
        break;

      case 2:
        std::cout << "Editing schedule...\n";
        break;

      case 3:
        std::cout << "Viewing festival lineup...\n";
        break;

      case 0:
        return;

      default:
        std::cout << "Invalid choice. Please try again.\n";
        break;
    }
  }
}

void showTicketSalesMenu() {
  int choice;

  while (true) {
    std::cout << "\n=== Ticket Sales Tracking ===\n";
    std::cout << "1. View Sales Data\n";
    std::cout << "2. Generate Reports\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "Select an option: ";
    std::cin >> choice;

    switch (choice) {
      case 1:
        std::cout << "Viewing sales data...\n";
        break;

      case 2:
        std::cout << "Generating reports...\n";
        break;

      case 0:
        return;

      default:
        std::cout << "Invalid choice. Please try again.\n";
        break;
    }
  }
}

void showVendorSponsorMenu() {
  int choice;

  while (true) {
    std::cout << "\n=== Vendor and Sponsor Coordination ===\n";
    std::cout << "1. Manage Vendors\n";
    std::cout << "2. Track Sponsors\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "Select an option: ";
    std::cin >> choice;

    switch (choice) {
      case 1:
        std::cout << "Managing vendors...\n";
        break;

      case 2:
        std::cout << "Tracking sponsors...\n";
        break;

      case 0:
        return;

      default:
        std::cout << "Invalid choice. Please try again.\n";
        break;
    }
  }
}

int main() {
  showMainMenu();
  return 0;
}
