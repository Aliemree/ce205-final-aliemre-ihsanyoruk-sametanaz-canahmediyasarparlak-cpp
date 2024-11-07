#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "publictransportationscheduler.h"
#include "publictransportationschedulerapp.h"
#include "../../publictransportationscheduler/src/publictransportationscheduler.cpp"

// Get console width for centering text
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}

// Center text in the console
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

// Center menu options with selection
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

void showUserAuthenticationMenu() {
    int choice = 0;
    const char* options[] = { "Login", "Register", "Guest Mode", "Back to Main Menu" };
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
        }
        else if (ch == 13) {
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
                }
                else {
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
// Route Management Menu
void showRouteManagementMenu() {
    int choice = 0;
    const char* options[] = { "Add Route", "Edit Route", "View Routes", "Delete Route", "Search Route", "Back to Main Menu" };
    int n_options = sizeof(options) / sizeof(options[0]);

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
            case 72: // Up arrow
                choice = (choice - 1 + n_options) % n_options;
                break;
            case 80: // Down arrow
                choice = (choice + 1) % n_options;
                break;
            }
        }
        else if (ch == 13) { // Enter key
            int routeID;
            char routeName[50];
            char startPoint[50];
            char endPoint[50];

            switch (choice) {
            case 0: { // Add Route
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
            }
            case 1: { // Edit Route
                printf("Enter route ID to edit: ");
                scanf("%d", &routeID);
                DoubleNode* routeNode = findDoubleNode(routeListHead, routeID);
                if (routeNode) {
                    printf("Enter new route name: ");
                    scanf("%s", routeName);
                    printf("Enter new starting point: ");
                    scanf("%s", startPoint);
                    printf("Enter new ending point: ");
                    scanf("%s", endPoint);
                    editRoute(routeNode, routeName, startPoint, endPoint);
                    printf("Route updated.\n");
                }
                else {
                    printf("Route not found.\n");
                }
                break;
            }
            case 2: { // View Routes
                printDetailedRouteList(routeListHead);
                break;
            }
            case 3: { // Delete Route
                printf("Enter route ID to delete: ");
                scanf("%d", &routeID);
                if (deleteDoubleNode(&routeListHead, routeID)) {
                    printf("Route deleted.\n");
                }
                else {
                    printf("Route not found.\n");
                }
                break;
            }
            case 4: { // Search Route
                printf("Enter route ID to search: ");
                scanf("%d", &routeID);
                DoubleNode* routeNode = findDoubleNode(routeListHead, routeID);
                if (routeNode) {
                    printf("Route found:\n");
                    printf("ID: %d | Name: %s | Start: %s | End: %s\n",
                        routeNode->data, routeNode->routeName, routeNode->startPoint, routeNode->endPoint);
                }
                else {
                    printf("Route not found.\n");
                }
                break;
            }
            case 5: { // Back to Main Menu
                return;
            }
            }
            system("pause");
        }
    }
}



// Scheduling Menu
void showSchedulingMenu() {
    int choice = 0;
    const char* options[] = { "Create Schedule", "Edit Schedule", "View Schedules", "Delete Schedule", "Back to Main Menu" };
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
            case 72: // Up arrow
                choice = (choice - 1 + n_options) % n_options;
                break;
            case 80: // Down arrow
                choice = (choice + 1) % n_options;
                break;
            }
        }
        else if (ch == 13) { // Enter key
            int scheduleID;
            char bandName[50], date[20];
            switch (choice) {
            case 0: // Create Schedule
                printf("Enter Schedule ID: ");
                scanf("%d", &scheduleID);
                printf("Enter Band/Artist Name: ");
                scanf("%s", bandName);
                printf("Enter Date (YYYY-MM-DD): ");
                scanf("%s", date);
                createSchedule(scheduleID, bandName, date);
                break;
            case 1: // Edit Schedule
                printf("Enter Schedule ID to edit: ");
                scanf("%d", &scheduleID);
                printf("Enter new Band/Artist Name: ");
                scanf("%s", bandName);
                printf("Enter new Date (YYYY-MM-DD): ");
                scanf("%s", date);
                editSchedule(scheduleID, bandName, date);
                break;
            case 2: // View Schedules
                viewSchedules();
                break;
            case 3: // Delete Schedule
                printf("Enter Schedule ID to delete: ");
                scanf("%d", &scheduleID);
                deleteSchedule(scheduleID);
                break;
            case 4: // Back to Main Menu
                return;
            }
            system("pause");
        }
    }
}

// Ticket Sales Menu
void showTicketSalesMenu() {
    int choice = 0;
    const char* options[] = { "View Sales Data", "Generate Sales Report", "Back to Main Menu" };
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
            case 72: // Up arrow
                choice = (choice - 1 + n_options) % n_options;
                break;
            case 80: // Down arrow
                choice = (choice + 1) % n_options;
                break;
            }
        }
        else if (ch == 13) { // Enter key
            switch (choice) {
            case 0: // View Sales Data
                loadSalesDatabase(); // Veritabanını yükle
                viewSalesData();
                break;
            case 1: // Generate Sales Report
                loadSalesDatabase(); // Veritabanını yükle
                generateSalesReport();
                break;
            case 2: // Back to Main Menu
                return;
            }
            system("pause");
        }
    }
}

// Data Management Menüsü
void showDataManagementMenu() {
    int choice = 0;
    const char* options[] = { "Add Vendor", "Add Sponsor", "Manage Vendors", "Track Sponsors", "Back to Main Menu" };
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
            case 72: // Up arrow
                choice = (choice - 1 + n_options) % n_options;
                break;
            case 80: // Down arrow
                choice = (choice + 1) % n_options;
                break;
            }
        }
        else if (ch == 13) { // Enter key
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
                return; // Back to Main Menu
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
            case 72: // Up arrow
                choice = (choice - 1 + (int)n_options) % (int)n_options;
                break;
            case 80: // Down arrow
                choice = (choice + 1) % (int)n_options;
                break;
            }
        }
        else if (ch == 13) { // Enter key
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

int main() {
    initializeHashTable();  // Initialize hash table at start
    showMainMenu();
    return 0;
}
