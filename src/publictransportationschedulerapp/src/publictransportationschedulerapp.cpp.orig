#include "publictransportationschedulerapp.h"
#include "publictransportationscheduler.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace Coruh::PublicTransportationScheduler;

// Dinamik ekran genişliğini almak için bir fonksiyon
int getConsoleWidth() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int columns;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  return columns;
}

// Dinamik ekran yüksekliğini almak için bir fonksiyon
int getConsoleHeight() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int rows;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  return rows;
}

// Metni ekranın ortasına hizalamak için fonksiyon
void centerText(const std::string &text) {
  int screenWidth = getConsoleWidth();
  int padding = (screenWidth - text.length()) / 2;
  std::cout << std::string(padding > 0 ? padding : 0, ' ') << text << "\n";
}

// Ekranı dikey olarak ortalamak için fonksiyon
void centerVertically(int contentHeight) {
  int screenHeight = getConsoleHeight();
  int padding = (screenHeight - contentHeight) / 2;

  for (int i = 0; i < padding; ++i) std::cout << "\n";
}

// İmleci gizlemek için fonksiyon
void hideCursor() {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 100;
  info.bVisible = FALSE;
  SetConsoleCursorInfo(consoleHandle, &info);
}

// İmleci göstermek için fonksiyon
void showCursor() {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 100;
  info.bVisible = TRUE;
  SetConsoleCursorInfo(consoleHandle, &info);
}

// Proje başlığı
void showProjectTitle() {
  centerText("=================================");
  centerText("   Public Transportation Scheduler   ");
  centerText("=================================\n");
}

// Otobüs resmi
void showBusArt() {
  centerText("          ___________________");
  centerText("         ||                 ||");
  centerText("         ||   BUS ROUTES    ||");
  centerText("         ||_________________||");
  centerText("      __||___________________||__");
  centerText("     |                           |");
  centerText("    (O)-----------------------(O)");
}

// Kullanıcı yönetimi için avatar
void showUserAuthArt() {
  centerText("        O");
  centerText("       /|\\");
  centerText("       / \\");
  centerText("    USER AUTHENTICATION");
}

// Sanatçılar ve etkinlikler için mikrofon
void showArtistArt() {
  centerText("        ________");
  centerText("       (________)");
  centerText("     .-'----------`-.");
  centerText("   /                  \\");
  centerText("  |     BAND & ARTIST  |");
  centerText("   \\__________________/");
}

// Çizelgeleme için saat resmi
void showScheduleArt() {
  centerText("       , - ~ ~ ~ - ,");
  centerText("   , '               ' ,");
  centerText("  ,                       ,");
  centerText(" ,        SCHEDULE         ,");
  centerText(" ,                           ,");
  centerText("   ' ,                   , '");
  centerText("      ' - , _ _ _ ,  '");
}

// Bilet satışı için bilet resmi
void showTicketArt() {
  centerText("     ________________");
  centerText("    /                /|");
  centerText("   /   TICKET SALES / |");
  centerText("  /________________ / /");
  centerText("  |                |/");
}

// Sponsor ve vendor yönetimi için el sıkışma
void showSponsorArt() {
  centerText("     O==[]=========>");
  centerText("         VENDORS & SPONSORS");
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
  int n_options = sizeof(options) / sizeof(options[0]);
  int contentHeight = 14;
  hideCursor();

  while (true) {
    system("cls");
    centerVertically(contentHeight);
    showProjectTitle();
    showBusArt();

    for (int i = 0; i < n_options; ++i) {
      if (i == choice) {
        centerText("> " + std::string(options[i]));
      } else {
        centerText("  " + std::string(options[i]));
      }
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
          showCursor();
          return;
      }
    }
  }
}

// Kullanıcı Kimlik Doğrulama Menüsü
void showUserAuthenticationMenu() {
  int choice = 0;
  const char *options[] = { "Login", "Register", "Guest Mode", "Back to Main Menu" };
  int n_options = sizeof(options) / sizeof(options[0]);
  int contentHeight = 12;
  hideCursor();

  while (true) {
    system("cls");
    centerVertically(contentHeight);
    showProjectTitle();
    showUserAuthArt();

    for (int i = 0; i < n_options; ++i) {
      if (i == choice) {
        centerText("> " + std::string(options[i]));
      } else {
        centerText("  " + std::string(options[i]));
      }
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
      system("cls");

      switch (choice) {
        case 3:
          showCursor();
          return;
      }

      system("pause");
    }
  }
}

// Band ve Artist Menüsü
void showBandManagementMenu() {
  int choice = 0;
  const char *options[] = { "Add Band/Artist", "Edit Band/Artist", "View Band/Artist List", "Back to Main Menu" };
  int n_options = sizeof(options) / sizeof(options[0]);
  int contentHeight = 12;
  hideCursor();

  while (true) {
    system("cls");
    centerVertically(contentHeight);
    showProjectTitle();
    showArtistArt();

    for (int i = 0; i < n_options; ++i) {
      if (i == choice) {
        centerText("> " + std::string(options[i]));
      } else {
        centerText("  " + std::string(options[i]));
      }
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
      system("cls");

      switch (choice) {
        case 3:
          showCursor();
          return;
      }

      system("pause");
    }
  }
}

// Çizelgeleme Menüsü
void showSchedulingMenu() {
  int choice = 0;
  const char *options[] = { "Create Schedule", "Edit Schedule", "View Festival Lineup", "Back to Main Menu" };
  int n_options = sizeof(options) / sizeof(options[0]);
  int contentHeight = 12;
  hideCursor();

  while (true) {
    system("cls");
    centerVertically(contentHeight);
    showProjectTitle();
    showScheduleArt();

    for (int i = 0; i < n_options; ++i) {
      if (i == choice) {
        centerText("> " + std::string(options[i]));
      } else {
        centerText("  " + std::string(options[i]));
      }
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
      system("cls");

      switch (choice) {
        case 3:
          showCursor();
          return;
      }

      system("pause");
    }
  }
}

// Bilet Satış Menüsü
void showTicketSalesMenu() {
  int choice = 0;
  const char *options[] = { "View Sales Data", "Generate Reports", "Back to Main Menu" };
  int n_options = sizeof(options) / sizeof(options[0]);
  int contentHeight = 10;
  hideCursor();

  while (true) {
    system("cls");
    centerVertically(contentHeight);
    showProjectTitle();
    showTicketArt();

    for (int i = 0; i < n_options; ++i) {
      if (i == choice) {
        centerText("> " + std::string(options[i]));
      } else {
        centerText("  " + std::string(options[i]));
      }
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
      system("cls");

      switch (choice) {
        case 2:
          showCursor();
          return;
      }

      system("pause");
    }
  }
}

// Sponsor ve Vendor Menüsü
void showVendorSponsorMenu() {
  int choice = 0;
  const char *options[] = { "Manage Vendors", "Track Sponsors", "Back to Main Menu" };
  int n_options = sizeof(options) / sizeof(options[0]);
  int contentHeight = 10;
  hideCursor();

  while (true) {
    system("cls");
    centerVertically(contentHeight);
    showProjectTitle();
    showSponsorArt();

    for (int i = 0; i < n_options; ++i) {
      if (i == choice) {
        centerText("> " + std::string(options[i]));
      } else {
        centerText("  " + std::string(options[i]));
      }
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
      system("cls");

      switch (choice) {
        case 2:
          showCursor();
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
