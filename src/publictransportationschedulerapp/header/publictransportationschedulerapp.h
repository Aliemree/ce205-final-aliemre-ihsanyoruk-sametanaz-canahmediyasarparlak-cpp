#ifndef PUBLICTRANSPORTATIONSCHEDULERAPP_H
#define PUBLICTRANSPORTATIONSCHEDULERAPP_H

// Helper function prototypes
void showMainMenu();
void showUserAuthenticationMenu();
void showBandManagementMenu();
void showSchedulingMenu();
void showTicketSalesMenu();
void showVendorSponsorMenu();

// Utility functions
int getConsoleWidth();
void centerText(const char* text);
void centerMenuOption(const char* text, int isSelected);

#endif // PUBLICTRANSPORTATIONSCHEDULERAPP_H
