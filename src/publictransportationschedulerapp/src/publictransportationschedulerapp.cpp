#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

// Dinamik ekran genişliği almak için bir işlev
int getConsoleWidth() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int columns;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  return columns;
}

// Metni ekranın ortasına hizalamak için bir işlev
void centerText(const char *text) {
  int screenWidth = getConsoleWidth();
  int padding = (screenWidth - strlen(text)) / 2;

  if (padding > 0) {
    printf("%*s%s\n", padding, "", text);
  } else {
    printf("%s\n", text);
  }
}

// Menü seçeneklerini ortalamak için bir işlev
void centerMenuOption(const char *text, int isSelected) {
  int screenWidth = getConsoleWidth();
  int padding = (screenWidth - strlen(text) - 2) / 2; // Seçili gösterim için ekstra boşluk

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

// Ana Menü
void showMainMenu();
void showUserAuthenticationMenu();
void showBandManagementMenu();
void showSchedulingMenu();
void showTicketSalesMenu();
void showVendorSponsorMenu();

// User Authentication Menu
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
      switch (choice) {
        case 0:
          printf("Username: ");
          char username[50], password[50];
          scanf("%s", username);
          printf("Password: ");
          scanf("%s", password);
          printf("Login function called for %s\n", username);
          break;

        case 1:
          printf("Register function\n");
          break;

        case 2:
          printf("Guest Mode activated.\n");
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

  while (1) {
    system("cls");
    centerText("=== Band and Artist Management ===\n");

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
          printf("Add Band/Artist function.\n");
          break;

        case 1:
          printf("Edit Band/Artist function.\n");
          break;

        case 2:
          printf("View Band/Artist List function.\n");
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

  while (1) {
    system("cls");
    centerText("=== Scheduling Performances ===\n");

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
          printf("Create Schedule function.\n");
          break;

        case 1:
          printf("Edit Schedule function.\n");
          break;

        case 2:
          printf("View Festival Lineup function.\n");
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

  while (1) {
    system("cls");
    centerText("=== Ticket Sales Tracking ===\n");

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
          printf("View Sales Data function.\n");
          break;

        case 1:
          printf("Generate Reports function.\n");
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

  while (1) {
    system("cls");
    centerText("=== Vendor and Sponsor Coordination ===\n");

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
          printf("Manage Vendors function.\n");
          break;

        case 1:
          printf("Track Sponsors function.\n");
          break;

        case 2:
          return;
      }

      system("pause");
    }
  }
}

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

      system("pause");
    }
  }
}

int main() {
  showMainMenu();
  return 0;
}
