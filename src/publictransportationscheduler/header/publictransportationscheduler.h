#ifndef PUBLICTRANSPORTATIONSCHEDULER_H
#define PUBLICTRANSPORTATIONSCHEDULER_H

#include <stdint.h>  // uintptr_t için

// Kullanıcı yapısı
typedef struct {
    char username[50];
    char password[50];
} User;

extern User userDatabase[100];
extern int userCount;

void loadUserDatabase();
void saveUserDatabase();
int login(const char* username, const char* password);
void registerUser(const char* username, const char* password);
void activateGuestMode();

// Band yapısı
typedef struct {
    char name[50];
} Band;

extern Band bandDatabase[100];
extern int bandCount;

void loadBandDatabase();
void saveBandDatabase();
void addBand(const char* name);
void editBand(const char* oldName, const char* newName);
void viewBands();

// Schedule yapısı
typedef struct {
    int scheduleID;
    char bandName[50];
    char date[20];
} Schedule;

extern Schedule scheduleDatabase[100];
extern int scheduleCount;

void loadScheduleDatabase();
void saveScheduleDatabase();
void createSchedule(int scheduleID, const char* bandName, const char* date);
void editSchedule(int scheduleID, const char* newBandName, const char* newDate);
void viewSchedules();

// Bilet satış verisi için yapı
typedef struct {
    int saleID;
    char ticketType[20];
    double amount;
    char date[20];
} TicketSale;

extern TicketSale salesDatabase[100];
extern int salesCount;

void loadSalesDatabase();
void saveSalesDatabase();
void viewSalesData();
void generateSalesReport();

// Satıcı yapısı
typedef struct {
    int vendorID;
    char name[50];
    char serviceType[50];
} Vendor;

extern Vendor vendorDatabase[100];
extern int vendorCount;

void loadVendorDatabase();
void saveVendorDatabase();
void manageVendors();

// Sponsor yapısı
typedef struct {
    int sponsorID;
    char name[50];
    double contributionAmount;
} Sponsor;

extern Sponsor sponsorDatabase[100];
extern int sponsorCount;

void loadSponsorDatabase();
void saveSponsorDatabase();
void trackSponsors();

// Ücret Hesaplama ve Gecikme Bildirimi İşlevleri
void calculateFare(const char* route, const char* ticketType);
void alertForDelays();

// Veriyi Sıkıştırma ve Açma (Örnek işlevler)
void compressAndSaveData(const char* data);
char* decompressData();

// Double Linked List İşlevleri
typedef struct DoubleNode {
    int data;
    struct DoubleNode* next;
    struct DoubleNode* prev;
} DoubleNode;

void insertDoubleNode(DoubleNode** head, int data);
void deleteDoubleNode(DoubleNode** head, int data);
void printDoubleList(DoubleNode* head);
void saveDoubleLinkedListToFile(DoubleNode* head, const char* filename);
void loadDoubleLinkedListFromFile(DoubleNode** head, const char* filename);

// XOR Linked List İşlevleri
typedef struct XORNode {
    int data;
    struct XORNode* npx;  // XOR of next and previous node
} XORNode;

XORNode* XOR(XORNode* a, XORNode* b);
void insertXORNode(XORNode** head, int data);
void printXORList(XORNode* head);
void saveXORLinkedListToFile(XORNode* head, const char* filename);
void loadXORLinkedListFromFile(XORNode** head, const char* filename);

// Seyrek Matris İşlevleri
typedef struct SparseMatrixNode {
    int row;
    int col;
    int value;
    struct SparseMatrixNode* next;
} SparseMatrixNode;

void insertSparseNode(SparseMatrixNode** head, int row, int col, int value);
void printSparseMatrix(SparseMatrixNode* head);
void saveSparseMatrixToFile(SparseMatrixNode* head, const char* filename);
void loadSparseMatrixFromFile(SparseMatrixNode** head, const char* filename);

#endif // PUBLICTRANSPORTATIONSCHEDULER_H
