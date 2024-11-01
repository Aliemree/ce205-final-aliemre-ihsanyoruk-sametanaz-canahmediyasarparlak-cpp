#include "publictransportationschedulerapp.h"
#include "publictransportationscheduler.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace Coruh::PublicTransportationScheduler;

// PublicTransportationScheduler sınıfının bir nesnesi
PublicTransportationScheduler scheduler;

// Dinamik ekran genişliği almak için bir işlev
int getConsoleWidth() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int columns;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  return columns;
}

// Metni ekranın ortasına hizalamak için bir işlev
void centerText(const std::string &text) {
  int screenWidth = getConsoleWidth();
  int padding = (screenWidth - text.length()) / 2;
  std::cout << std::string(padding > 0 ? padding : 0, ' ') << text << "\n";
}

// Ana Menü
void showMainMenu() {
  int choice = 0;
  const char *options[] = {
    "User Authentication",
    "Band and Artist Management",
    "Scheduling Performances",
    "Ticket Sales Tracking",
    "Vendor and Sponsor Coordination",
    "Exit"
  };
  size_t n_options = sizeof(options) / sizeof(options[0]);  // `size_t` olarak değiştirildi

  while (true) {
    system("cls");
    centerText("=================================");
    centerText("   Public Transportation Scheduler   ");
    centerText("=================================\n");

    for (size_t i = 0; i < n_options; ++i) {
      if (i == choice) centerText("> " + std::string(options[i]));
      else centerText("  " + std::string(options[i]));
    }

    int ch = _getch();

    if (ch == 224) {
      ch = _getch();

      switch (ch) {
        case 72:
          choice = (choice - 1 + static_cast<int>(n_options)) % static_cast<int>(n_options);
          break;

        case 80:
          choice = (choice + 1) % static_cast<int>(n_options);
          break;
      }
    } else if (ch == 13) {
      switch (choice) {
        case 0:
          showUserAuthenticationMenu();
          break;

        case 1:
          showBandManagementMenu();
          break;

        case 2:
          showSchedulingMenu();
          break;

        case 3:
          showTicketSalesMenu();
          break;

        case 4:
          showVendorSponsorMenu();
          break;

        case 5:
          return;
      }
    }
  }
}

// User Authentication Menu
void showUserAuthenticationMenu() {
  int choice = 0;
  const char *options[] = { "Login", "Register", "Guest Mode", "Back to Main Menu" };
  int n_options = sizeof(options) / sizeof(options[0]);

  while (true) {
    system("cls");
    centerText("=== User Authentication ===\n");

    for (int i = 0; i < n_options; ++i) {
      if (i == choice) centerText("> " + std::string(options[i]));
      else centerText("  " + std::string(options[i]));
    }

    int ch = _getch();

    if (ch == 224) {
      ch = _getch();

      switch (ch) {
        case 72:
          choice = (choice - 1 + n_options) % n_options;
          break;

        case 80:
          choice = (choice + 1) % n_options;
          break;
      }
    } else if (ch == 13) {
      switch (choice) {
        case 0: {
          std::string username, password;
          std::cout << "Username: ";
          std::cin >> username;
          std::cout << "Password: ";
          std::cin >> password;
          scheduler.login(username, password);
          break;
        }

        case 1: {
          std::string username, password;
          std::cout << "Username: ";
          std::cin >> username;
          std::cout << "Password: ";
          std::cin >> password;
          scheduler.registerUser(username, password);
          break;
        }

        case 2:
          std::cout << "Guest Mode activated.\n";
          break;

        case 3:
          return;
      }

      system("pause");
    }
  }
}

// Band and Artist Management Menu
void showBandManagementMenu() {
  int choice = 0;
  const char *options[] = { "Add Band/Artist", "Edit Band/Artist", "View Band/Artist List", "Back to Main Menu" };
  int n_options = sizeof(options) / sizeof(options[0]);

  while (true) {
    system("cls");
    centerText("=== Band and Artist Management ===\n");

    for (int i = 0; i < n_options; ++i) {
      if (i == choice) centerText("> " + std::string(options[i]));
      else centerText("  " + std::string(options[i]));
    }

    int ch = _getch();

    if (ch == 224) {
      ch = _getch();

      switch (ch) {
        case 72:
          choice = (choice - 1 + n_options) % n_options;
          break;

        case 80:
          choice = (choice + 1) % n_options;
          break;
      }
    } else if (ch == 13) {
      switch (choice) {
        case 0:
          std::cout << "Add Band/Artist function.\n";
          break;

        case 1:
          std::cout << "Edit Band/Artist function.\n";
          break;

        case 2:
          std::cout << "View Band/Artist List function.\n";
          break;

        case 3:
          return;
      }

      system("pause");
    }
  }
}

// Scheduling Performances Menu
void showSchedulingMenu() {
  int choice = 0;
  const char *options[] = { "Create Schedule", "Edit Schedule", "View Festival Lineup", "Back to Main Menu" };
  int n_options = sizeof(options) / sizeof(options[0]);

  while (true) {
    system("cls");
    centerText("=== Scheduling Performances ===\n");

    for (int i = 0; i < n_options; ++i) {
      if (i == choice) centerText("> " + std::string(options[i]));
      else centerText("  " + std::string(options[i]));
    }

    int ch = _getch();

    if (ch == 224) {
      ch = _getch();

      switch (ch) {
        case 72:
          choice = (choice - 1 + n_options) % n_options;
          break;

        case 80:
          choice = (choice + 1) % n_options;
          break;
      }
    } else if (ch == 13) {
      switch (choice) {
        case 0:
          std::cout << "Create Schedule function.\n";
          break;

        case 1:
          std::cout << "Edit Schedule function.\n";
          break;

        case 2:
          std::cout << "View Festival Lineup function.\n";
          break;

        case 3:
          return;
      }

      system("pause");
    }
  }
}

// Ticket Sales Tracking Menu
void showTicketSalesMenu() {
  int choice = 0;
  const char *options[] = { "View Sales Data", "Generate Reports", "Back to Main Menu" };
  int n_options = sizeof(options) / sizeof(options[0]);

  while (true) {
    system("cls");
    centerText("=== Ticket Sales Tracking ===\n");

    for (int i = 0; i < n_options; ++i) {
      if (i == choice) centerText("> " + std::string(options[i]));
      else centerText("  " + std::string(options[i]));
    }

    int ch = _getch();

    if (ch == 224) {
      ch = _getch();

      switch (ch) {
        case 72:
          choice = (choice - 1 + n_options) % n_options;
          break;

        case 80:
          choice = (choice + 1) % n_options;
          break;
      }
    } else if (ch == 13) {
      switch (choice) {
        case 0:
          std::cout << "View Sales Data function.\n";
          break;

        case 1:
          std::cout << "Generate Reports function.\n";
          break;

        case 2:
          return;
      }

      system("pause");
    }
  }
}

// Vendor and Sponsor Coordination Menu
void showVendorSponsorMenu() {
  int choice = 0;
  const char *options[] = { "Manage Vendors", "Track Sponsors", "Back to Main Menu" };
  int n_options = sizeof(options) / sizeof(options[0]);

  while (true) {
    system("cls");
    centerText("=== Vendor and Sponsor Coordination ===\n");

    for (int i = 0; i < n_options; ++i) {
      if (i == choice) centerText("> " + std::string(options[i]));
      else centerText("  " + std::string(options[i]));
    }

    int ch = _getch();

    if (ch == 224) {
      ch = _getch();

      switch (ch) {
        case 72:
          choice = (choice - 1 + n_options) % n_options;
          break;

        case 80:
          choice = (choice + 1) % n_options;
          break;
      }
    } else if (ch == 13) {
      switch (choice) {
        case 0:
          std::cout << "Manage Vendors function.\n";
          break;

        case 1:
          std::cout << "Track Sponsors function.\n";
          break;

        case 2:
          return;
      }

      system("pause");
    }
  }
}

int main() {
  showMainMenu();
  return 0;
}
