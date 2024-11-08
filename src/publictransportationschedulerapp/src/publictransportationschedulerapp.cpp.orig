#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "publictransportationscheduler.h"
#include "publictransportationschedulerapp.h"
#include "../../publictransportationscheduler/src/publictransportationscheduler.cpp"

/**
 * @brief Gets the width of the console for centering text.
 * @return Width of the console.
 */
int getConsoleWidth() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int columns;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  return columns;
}

/**
 * @brief Centers the given text in the console.
 * @param text The text to center in the console.
 */
void centerText(const char *text) {
  int screenWidth = getConsoleWidth();
  int padding = (screenWidth - strlen(text)) / 2;

  if (padding > 0) {
    printf("%*s%s\n", padding, "", text);
  } else {
    printf("%s\n", text);
  }
}

/**
 * @brief Centers the menu option text and highlights if selected.
 * @param text The menu option text.
 * @param isSelected Flag indicating if the option is selected.
 */
void centerMenuOption(const char *text, int isSelected) {
  int screenWidth = getConsoleWidth();
  int padding = (screenWidth - strlen(text) - 2) / 2;

  if (padding > 0) {
    if (isSelected) {
      printf("%*s> %s\n", padding, "", text);
    } else {
      printf("%*s  %s\n", padding, "", text);
    }
  } else {
    if (isSelected) {
      printf("> %s\n", text);
    } else {
      printf("  %s\n", text);
    }
  }
}

/**
 * @brief Displays the user authentication menu with options to login, register, or access as guest.
 */
void showUserAuthenticationMenu() {
  int choice = 0;
  const char *options[] = { "Login", "Register", "Guest Mode", "Back to Main Menu" };
  int n_options = sizeof(options) / sizeof(options[0]);

  while (1) {
    system("cls");
    centerText("=== User Authentication ===\n");

    for (int i = 0; i < n_options; ++i) {
      centerMenuOption(options[i], i == choice);
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
      char username[50], password[50];

      switch (choice) {
        case 0:
          printf("Username: ");
          scanf("%s", username);
          printf("Password: ");
          scanf("%s", password);

          if (verifyUserInHashTable(username, password)) {
            printf("Login successful. Redirecting to main menu...\n");
            return;
          } else {
            printf("Invalid username or password.\n");
          }

          break;

        case 1:
          printf("Username: ");
          scanf("%s", username);
          printf("Password: ");
          scanf("%s", password);
          addUserToHashTable(username, password);
          printf("User registered successfully. Logging in...\n");

          if (verifyUserInHashTable(username, password)) {
            printf("Registration and login successful. Redirecting to main menu...\n");
            return;
          }

          break;

        case 2:
          printf("Guest Mode activated. Limited access granted.\n");
          return;

        case 3:
          return;
      }

      system("pause");
    }
  }
}

/**
 * @brief Displays the route management menu with options to add, edit, view, delete, and search routes.
 */
void showRouteManagementMenu() {
  int choice = 0;
  const char *options[] = { "Add Route", "Edit Route", "View Routes", "Delete Route", "Search Route", "Back to Main Menu" };
  int n_options = sizeof(options) / sizeof(options[0]);
  int routeID;
  char routeName[50];
  char startPoint[50];
  char endPoint[50];
  DoubleNode *routeNode = NULL; // routeNode'u burada tanımlayın

  while (1) {
    system("cls");
    centerText("=== Route Management ===\n");

    for (int i = 0; i < n_options; ++i) {
      centerMenuOption(options[i], i == choice);
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
          printf("Enter route ID: ");
          scanf("%d", &routeID);
          printf("Enter route name: ");
          scanf("%s", routeName);
          printf("Enter starting point: ");
          scanf("%s", startPoint);
          printf("Enter ending point: ");
          scanf("%s", endPoint);
          addRoute(routeID, routeName, startPoint, endPoint);
          printf("Route added.\n");
          break;

        case 1:
          printf("Enter route ID to edit: ");
          scanf("%d", &routeID);
          routeNode = findDoubleNode(routeListHead, routeID);

          if (routeNode) {
            printf("Enter new route name: ");
            scanf("%s", routeName);
            printf("Enter new starting point: ");
            scanf("%s", startPoint);
            printf("Enter new ending point: ");
            scanf("%s", endPoint);
            editRoute(routeNode, routeName, startPoint, endPoint);
            printf("Route updated.\n");
          } else {
            printf("Route not found.\n");
          }

          break;

        case 2:
          printDetailedRouteList(routeListHead);
          break;

        case 3:
          printf("Enter route ID to delete: ");
          scanf("%d", &routeID);

          if (deleteDoubleNode(&routeListHead, routeID)) {
            printf("Route deleted.\n");
          } else {
            printf("Route not found.\n");
          }

          break;

        case 4:
          printf("Enter route ID to search: ");
          scanf("%d", &routeID);
          routeNode = findDoubleNode(routeListHead, routeID);

          if (routeNode) {
            printf("Route found:\n");
            printf("ID: %d | Name: %s | Start: %s | End: %s\n", routeNode->data, routeNode->routeName, routeNode->startPoint, routeNode->endPoint);
          } else {
            printf("Route not found.\n");
          }

          break;

        case 5:
          return;
      }

      system("pause");
    }
  }
}

/**
 * @brief Displays the scheduling menu with options to create, edit, view, and delete schedules.
 */
void showSchedulingMenu() {
  int choice = 0;
  const char *options[] = { "Create Schedule", "Edit Schedule", "View Schedules", "Delete Schedule", "Back to Main Menu" };
  int n_options = sizeof(options) / sizeof(options[0]);

  while (1) {
    system("cls");
    centerText("=== Scheduling ===\n");

    for (int i = 0; i < n_options; ++i) {
      centerMenuOption(options[i], i == choice);
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
      int scheduleID;
      char bandName[50], date[20];

      switch (choice) {
        case 0:
          printf("Enter Schedule ID: ");
          scanf("%d", &scheduleID);
          printf("Enter Band/Artist Name: ");
          scanf("%s", bandName);
          printf("Enter Date (YYYY-MM-DD): ");
          scanf("%s", date);
          createSchedule(scheduleID, bandName, date);
          break;

        case 1:
          printf("Enter Schedule ID to edit: ");
          scanf("%d", &scheduleID);
          printf("Enter new Band/Artist Name: ");
          scanf("%s", bandName);
          printf("Enter new Date (YYYY-MM-DD): ");
          scanf("%s", date);
          editSchedule(scheduleID, bandName, date);
          break;

        case 2:
          viewSchedules();
          break;

        case 3:
          printf("Enter Schedule ID to delete: ");
          scanf("%d", &scheduleID);
          deleteSchedule(scheduleID);
          break;

        case 4:
          return;
      }

      system("pause");
    }
  }
}

/**
 * @brief Displays the ticket sales menu with options to view, search, report, and manage B+ tree data.
 */
void showTicketSalesMenu() {
  int choice = 0;
  const char *options[] = { "View Sales Data", "Generate Sales Report", "Search Sale by ID", "Display B+ Tree", "Back to Main Menu" };
  int n_options = sizeof(options) / sizeof(options[0]);

  while (1) {
    system("cls");
    centerText("=== Ticket Sales ===\n");

    for (int i = 0; i < n_options; ++i) {
      centerMenuOption(options[i], i == choice);
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
          saveSampleSalesData();
          loadSalesDatabase();
          viewSalesData();
          break;

        case 1:
          loadSalesDatabase();
          generateSalesReport();
          break;

        case 2: {
          int saleID;
          printf("Enter Sale ID to search: ");
          scanf("%d", &saleID);
          TicketSale *sale = searchBPlusTree(saleID);

          if (sale) {
            printf("Sale ID: %d, Type: %s, Amount: %.2f, Date: %s\n", sale->saleID, sale->ticketType, sale->amount, sale->date);
          } else {
            printf("Sale not found.\n");
          }

          break;
        }

        case 3:
          displayBPlusTree(root);
          break;

        case 4:
          return;
      }

      system("pause");
    }
  }
}

/**
 * @brief Displays the data management menu with options to add and manage vendors and sponsors.
 */
void showDataManagementMenu() {
  int choice = 0;
  const char *options[] = { "Add Vendor", "Add Sponsor", "Manage Vendors", "Track Sponsors", "Back to Main Menu" };
  int n_options = sizeof(options) / sizeof(options[0]);

  while (1) {
    system("cls");
    centerText("=== Data Management ===\n");

    for (int i = 0; i < n_options; ++i) {
      centerMenuOption(options[i], i == choice);
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
          addVendorMenu();
          break;

        case 1:
          addSponsorMenu();
          break;

        case 2:
          manageVendors();
          break;

        case 3:
          trackSponsors();
          break;

        case 4:
          return;
      }

      system("pause");
    }
  }
}

/**
 * @brief Displays the main menu with options to access different parts of the system.
 */
void showMainMenu() {
  int choice = 0;
  const char *options[] = {
    "User Authentication",
    "Route Management",
    "Scheduling",
    "Ticket Sales",
    "Data Management",
    "Exit"
  };
  size_t n_options = sizeof(options) / sizeof(options[0]);

  while (1) {
    system("cls");
    centerText("=================================");
    centerText("   Public Transportation Scheduler   ");
    centerText("=================================\n");

    for (size_t i = 0; i < n_options; ++i) {
      centerMenuOption(options[i], i == choice);
    }

    int ch = _getch();

    if (ch == 224) {
      ch = _getch();

      switch (ch) {
        case 72:
          choice = (choice - 1 + (int)n_options) % (int)n_options;
          break;

        case 80:
          choice = (choice + 1) % (int)n_options;
          break;
      }
    } else if (ch == 13) {
      switch (choice) {
        case 0:
          showUserAuthenticationMenu();
          break;

        case 1:
          showRouteManagementMenu();
          break;

        case 2:
          showSchedulingMenu();
          break;

        case 3:
          showTicketSalesMenu();
          break;

        case 4:
          showDataManagementMenu();
          break;

        case 5:
          return;
      }

      system("pause");
    }
  }
}

/**
 * @brief The main function to initialize and show the main menu.
 * @return Program exit status.
 */
int main() {
  initializeHashTable();
  showMainMenu();
  return 0;
}
