#ifndef PUBLICTRANSPORTATIONSCHEDULERAPP_H
#define PUBLICTRANSPORTATIONSCHEDULERAPP_H

// Yardımcı işlev prototipleri
void showMainMenu();
void showUserAuthenticationMenu();
void showBandManagementMenu();
void showSchedulingMenu();
void showTicketSalesMenu();
void showVendorSponsorMenu();

// Yardımcı Fonksiyonlar
int getConsoleWidth();
void centerText(const char* text);
void centerMenuOption(const char* text, int isSelected);

#endif // PUBLICTRANSPORTATIONSCHEDULERAPP_H
