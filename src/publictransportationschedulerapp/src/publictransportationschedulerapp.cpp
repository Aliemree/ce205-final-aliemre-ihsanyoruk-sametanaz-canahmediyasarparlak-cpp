#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "publictransportationscheduler.h"
#include "publictransportationschedulerapp.h"

// Function to dynamically get console width
/**
 * Gets the current width of the console window.
 * @return The width of the console in characters
 */
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}

// Function to center-align text in the console
/**
 * Centers and displays text in the console.
 * @param text The text to be centered and displayed
 */
void centerText(const char* text) {
    int screenWidth = getConsoleWidth();
    int padding = (screenWidth - strlen(text)) / 2;

    if (padding > 0) {
        printf("%*s%s\n", padding, "", text);
    }
    else {
        printf("%s\n", text);
    }
}

// Function to center-align menu options with selection indicator
/**
 * Centers a menu option in the console with an indicator if selected.
 * @param text The menu option text
 * @param isSelected A flag indicating if the option is selected (1 for selected, 0 otherwise)
 */
void centerMenuOption(const char* text, int isSelected) {
    int screenWidth = getConsoleWidth();
    int padding = (screenWidth - strlen(text) - 2) / 2;

    if (padding > 0) {
        if (isSelected) {
            printf("%*s> %s\n", padding, "", text);
        }
        else {
            printf("%*s  %s\n", padding, "", text);
        }
    }
    else {
        if (isSelected) {
            printf("> %s\n", text);
        }
        else {
            printf("  %s\n", text);
        }
    }
}

// User Authentication Menu
void showUserAuthenticationMenu() {
    int choice = 0;
    const char* options[] = { "Login", "Register", "Guest Mode", "Back to Main Menu" };
    int n_options = sizeof(options) / sizeof(options[0]);

    while (1) {
        system("cls");
        centerText("=== User Authentication ===\n");

        // Display each option in the menu, highlighting the selected one
        for (int i = 0; i < n_options; ++i) {
            centerMenuOption(options[i], i == choice);
        }

        int ch = _getch();

        if (ch == 224) { // Handle arrow key inputs
            ch = _getch();
            switch (ch) {
            case 72: // Up arrow
                choice = (choice - 1 + n_options) % n_options;
                break;
            case 80: // Down arrow
                choice = (choice + 1) % n_options;
                break;
            }
        }
        else if (ch == 13) { // Enter key to select an option
            char username[50], password[50];
            switch (choice) {
            case 0: // Login
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");
                scanf("%s", password);
                login(username, password);
                break;
            case 1: // Register
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");
                scanf("%s", password);
                registerUser(username, password);
                break;
            case 2: // Guest Mode
                activateGuestMode();
                break;
            case 3: // Back to Main Menu
                return;
            }
            system("pause");
        }
    }
}

// Band and Artist Management Menu
void showBandManagementMenu() {
    int choice = 0;
    const char* options[] = { "Add Band/Artist", "Edit Band/Artist", "View Band/Artist List", "Back to Main Menu" };
    int n_options = sizeof(options) / sizeof(options[0]);

    while (1) {
        system("cls");
        centerText("=== Band and Artist Management ===\n");

        // Display each option in the menu, highlighting the selected one
        for (int i = 0; i < n_options; ++i) {
            centerMenuOption(options[i], i == choice);
        }

        int ch = _getch();

        if (ch == 224) { // Handle arrow key inputs
            ch = _getch();
            switch (ch) {
            case 72: // Up arrow
                choice = (choice - 1 + n_options) % n_options;
                break;
            case 80: // Down arrow
                choice = (choice + 1) % n_options;
                break;
            }
        }
        else if (ch == 13) { // Enter key to select an option
            char bandName[50], oldName[50], newName[50];
            switch (choice) {
            case 0: // Add Band/Artist
                printf("Enter Band/Artist Name: ");
                scanf("%s", bandName);
                addBand(bandName);
                break;
            case 1: // Edit Band/Artist
                printf("Enter Current Name of Band/Artist: ");
                scanf("%s", oldName);
                printf("Enter New Name of Band/Artist: ");
                scanf("%s", newName);
                editBand(oldName, newName);
                break;
            case 2: // View Band/Artist List
                viewBands();
                break;
            case 3: // Back to Main Menu
                return;
            }
            system("pause");
        }
    }
}

// Scheduling Performances Menu
void showSchedulingMenu() {
    int choice = 0;
    const char* options[] = { "Create Schedule", "Edit Schedule", "View Festival Lineup", "Back to Main Menu" };
    int n_options = sizeof(options) / sizeof(options[0]);

    while (1) {
        system("cls");
        centerText("=== Scheduling Performances ===\n");

        // Display each option in the menu, highlighting the selected one
        for (int i = 0; i < n_options; ++i) {
            centerMenuOption(options[i], i == choice);
        }

        int ch = _getch();

        if (ch == 224) { // Handle arrow key inputs
            ch = _getch();
            switch (ch) {
            case 72: // Up arrow
                choice = (choice - 1 + n_options) % n_options;
                break;
            case 80: // Down arrow
                choice = (choice + 1) % n_options;
                break;
            }
        }
        else if (ch == 13) { // Enter key to select an option
            int scheduleID;
            char bandName[50], date[20], newBandName[50], newDate[20];
            switch (choice) {
            case 0: // Create Schedule
                printf("Enter Schedule ID: ");
                scanf("%d", &scheduleID);
                printf("Enter Band/Artist Name: ");
                scanf("%s", bandName);
                printf("Enter Date (e.g., YYYY-MM-DD): ");
                scanf("%s", date);
                createSchedule(scheduleID, bandName, date);
                break;
            case 1: // Edit Schedule
                printf("Enter Schedule ID to Edit: ");
                scanf("%d", &scheduleID);
                printf("Enter New Band/Artist Name: ");
                scanf("%s", newBandName);
                printf("Enter New Date (e.g., YYYY-MM-DD): ");
                scanf("%s", newDate);
                editSchedule(scheduleID, newBandName, newDate);
                break;
            case 2: // View Festival Lineup
                viewSchedules();
                break;
            case 3: // Back to Main Menu
                return;
            }
            system("pause");
        }
    }
}

// Ticket Sales Tracking Menu
void showTicketSalesMenu() {
    int choice = 0;
    const char* options[] = { "View Sales Data", "Generate Reports", "Back to Main Menu" };
    int n_options = sizeof(options) / sizeof(options[0]);

    while (1) {
        system("cls");
        centerText("=== Ticket Sales Tracking ===\n");

        // Display each option in the menu, highlighting the selected one
        for (int i = 0; i < n_options; ++i) {
            centerMenuOption(options[i], i == choice);
        }

        int ch = _getch();

        if (ch == 224) { // Handle arrow key inputs
            ch = _getch();
            switch (ch) {
            case 72: // Up arrow
                choice = (choice - 1 + n_options) % n_options;
                break;
            case 80: // Down arrow
                choice = (choice + 1) % n_options;
                break;
            }
        }
        else if (ch == 13) { // Enter key to select an option
            switch (choice) {
            case 0: // View Sales Data
                viewSalesData();
                break;
            case 1: // Generate Reports
                generateSalesReport();
                break;
            case 2: // Back to Main Menu
                return;
            }
            system("pause");
        }
    }
}

// Vendor and Sponsor Coordination Menu
void showVendorSponsorMenu() {
    int choice = 0;
    const char* options[] = { "Manage Vendors", "Track Sponsors", "Back to Main Menu" };
    int n_options = sizeof(options) / sizeof(options[0]);

    while (1) {
        system("cls");
        centerText("=== Vendor and Sponsor Coordination ===\n");

        // Display each option in the menu, highlighting the selected one
        for (int i = 0; i < n_options; ++i) {
            centerMenuOption(options[i], i == choice);
        }

        int ch = _getch();

        if (ch == 224) { // Handle arrow key inputs
            ch = _getch();
            switch (ch) {
            case 72: // Up arrow
                choice = (choice - 1 + n_options) % n_options;
                break;
            case 80: // Down arrow
                choice = (choice + 1) % n_options;
                break;
            }
        }
        else if (ch == 13) { // Enter key to select an option
            switch (choice) {
            case 0: // Manage Vendors
                manageVendors();
                break;
            case 1: // Track Sponsors
                trackSponsors();
                break;
            case 2: // Back to Main Menu
                return;
            }
            system("pause");
        }
    }
}

// Main Menu Function
void showMainMenu() {
    int choice = 0;
    const char* options[] = {
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

        // Display each option in the menu, highlighting the selected one
        for (size_t i = 0; i < n_options; ++i) {
            centerMenuOption(options[i], i == choice);
        }

        int ch = _getch();

        if (ch == 224) { // Handle arrow key inputs
            ch = _getch();
            switch (ch) {
            case 72: // Up arrow
                choice = (choice - 1 + (int)n_options) % (int)n_options;
                break;
            case 80: // Down arrow
                choice = (choice + 1) % (int)n_options;
                break;
            }
        }
        else if (ch == 13) { // Enter key to select an option
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

// Main function to run the program
int main() {
    showMainMenu();
    return 0;
}
