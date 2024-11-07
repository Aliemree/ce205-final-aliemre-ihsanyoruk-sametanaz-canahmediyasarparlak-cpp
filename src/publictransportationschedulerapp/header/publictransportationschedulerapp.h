#ifndef PUBLICTRANSPORTATIONSCHEDULERAPP_H
#define PUBLICTRANSPORTATIONSCHEDULERAPP_H

#include "publictransportationscheduler.h"

/**
 * @brief Displays the main menu with options to access different parts of the system.
 */
void showMainMenu();

/**
 * @brief Displays the user authentication menu with options to login, register, or access as guest.
 */
void showUserAuthenticationMenu();

/**
 * @brief Displays the route management menu with options to add, edit, view, delete, and search routes.
 */
void showRouteManagementMenu();

/**
 * @brief Displays the scheduling menu with options to create, edit, view, and delete schedules.
 */
void showSchedulingMenu();

/**
 * @brief Displays the ticket sales menu with options to view, search, report, and manage B+ tree data.
 */
void showTicketSalesMenu();

/**
 * @brief Displays the data management menu with options to add and manage vendors and sponsors.
 */
void showDataManagementMenu();

/**
 * @brief Gets the width of the console for centering text.
 * @return Width of the console.
 */
int getConsoleWidth();

/**
 * @brief Centers the given text in the console.
 * @param text The text to center in the console.
 */
void centerText(const char* text);

/**
 * @brief Centers the menu option text and highlights if selected.
 * @param text The menu option text.
 * @param isSelected Flag indicating if the option is selected.
 */
void centerMenuOption(const char* text, int isSelected);

#endif // PUBLICTRANSPORTATIONSCHEDULERAPP_H
