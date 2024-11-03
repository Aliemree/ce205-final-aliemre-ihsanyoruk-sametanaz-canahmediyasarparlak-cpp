#include "publictransportationscheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // uintptr_t için

// Kullanıcı, band ve schedule veritabanı tanımları
int userCount = 0;
User userDatabase[100];

int bandCount = 0;
Band bandDatabase[100];

int scheduleCount = 0;
Schedule scheduleDatabase[100];

// Bilet satış veritabanı
TicketSale salesDatabase[100];
int salesCount = 0;

// Satıcı veritabanı
Vendor vendorDatabase[100];
int vendorCount = 0;

// Sponsor veritabanı
Sponsor sponsorDatabase[100];
int sponsorCount = 0;

// XOR işlevi
XORNode* XOR(XORNode* a, XORNode* b) {
    return (XORNode*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

// Kullanıcı Doğrulama İşlemleri
void loadUserDatabase() {
    FILE* file;
    fopen_s(&file, "userDatabase.bin", "rb");
    if (file) {
        fread(&userCount, sizeof(int), 1, file);
        fread(userDatabase, sizeof(User), userCount, file);
        fclose(file);
    }
}

void saveUserDatabase() {
    FILE* file;
    fopen_s(&file, "userDatabase.bin", "wb");
    fwrite(&userCount, sizeof(int), 1, file);
    fwrite(userDatabase, sizeof(User), userCount, file);
    fclose(file);
}

int login(const char* username, const char* password) {
    loadUserDatabase();
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userDatabase[i].username, username) == 0 &&
            strcmp(userDatabase[i].password, password) == 0) {
            printf("Login successful.\n");
            return 1;
        }
    }
    printf("Invalid username or password.\n");
    return 0;
}

void registerUser(const char* username, const char* password) {
    loadUserDatabase();
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userDatabase[i].username, username) == 0) {
            printf("Username already exists.\n");
            return;
        }
    }
    strcpy_s(userDatabase[userCount].username, sizeof(userDatabase[userCount].username), username);
    strcpy_s(userDatabase[userCount].password, sizeof(userDatabase[userCount].password), password);
    userCount++;
    saveUserDatabase();
    printf("User registered successfully.\n");
}

void activateGuestMode() {
    printf("Guest Mode activated. Limited access granted.\n");
}

// Band ve Sanatçı Yönetimi İşlemleri
void loadBandDatabase() {
    FILE* file;
    fopen_s(&file, "bandDatabase.bin", "rb");
    if (file) {
        fread(&bandCount, sizeof(int), 1, file);
        fread(bandDatabase, sizeof(Band), bandCount, file);
        fclose(file);
    }
}

void saveBandDatabase() {
    FILE* file;
    fopen_s(&file, "bandDatabase.bin", "wb");
    fwrite(&bandCount, sizeof(int), 1, file);
    fwrite(bandDatabase, sizeof(Band), bandCount, file);
    fclose(file);
}

void addBand(const char* name) {
    loadBandDatabase();
    strcpy_s(bandDatabase[bandCount].name, sizeof(bandDatabase[bandCount].name), name);
    bandCount++;
    saveBandDatabase();
    printf("Band/Artist %s added.\n", name);
}

void editBand(const char* oldName, const char* newName) {
    loadBandDatabase();
    for (int i = 0; i < bandCount; i++) {
        if (strcmp(bandDatabase[i].name, oldName) == 0) {
            strcpy_s(bandDatabase[i].name, sizeof(bandDatabase[i].name), newName);
            saveBandDatabase();
            printf("Band/Artist %s updated to %s.\n", oldName, newName);
            return;
        }
    }
    printf("Band/Artist %s not found.\n", oldName);
}

void viewBands() {
    loadBandDatabase();
    printf("Band and Artist List:\n");
    for (int i = 0; i < bandCount; i++) {
        printf("%s\n", bandDatabase[i].name);
    }
}

// Schedule İşlemleri
void loadScheduleDatabase() {
    FILE* file;
    fopen_s(&file, "scheduleDatabase.bin", "rb");
    if (file) {
        fread(&scheduleCount, sizeof(int), 1, file);
        fread(scheduleDatabase, sizeof(Schedule), scheduleCount, file);
        fclose(file);
    }
}

void saveScheduleDatabase() {
    FILE* file;
    fopen_s(&file, "scheduleDatabase.bin", "wb");
    fwrite(&scheduleCount, sizeof(int), 1, file);
    fwrite(scheduleDatabase, sizeof(Schedule), scheduleCount, file);
    fclose(file);
}

void createSchedule(int scheduleID, const char* bandName, const char* date) {
    loadScheduleDatabase();
    scheduleDatabase[scheduleCount].scheduleID = scheduleID;
    strcpy_s(scheduleDatabase[scheduleCount].bandName, sizeof(scheduleDatabase[scheduleCount].bandName), bandName);
    strcpy_s(scheduleDatabase[scheduleCount].date, sizeof(scheduleDatabase[scheduleCount].date), date);
    scheduleCount++;
    saveScheduleDatabase();
    printf("Schedule created for band %s on %s.\n", bandName, date);
}

void editSchedule(int scheduleID, const char* newBandName, const char* newDate) {
    loadScheduleDatabase();
    for (int i = 0; i < scheduleCount; i++) {
        if (scheduleDatabase[i].scheduleID == scheduleID) {
            strcpy_s(scheduleDatabase[i].bandName, sizeof(scheduleDatabase[i].bandName), newBandName);
            strcpy_s(scheduleDatabase[i].date, sizeof(scheduleDatabase[i].date), newDate);
            saveScheduleDatabase();
            printf("Schedule %d updated to band %s on %s.\n", scheduleID, newBandName, newDate);
            return;
        }
    }
    printf("Schedule %d not found.\n", scheduleID);
}

void viewSchedules() {
    loadScheduleDatabase();
    printf("Festival Lineup:\n");
    for (int i = 0; i < scheduleCount; i++) {
        printf("ID: %d | Band: %s | Date: %s\n", scheduleDatabase[i].scheduleID, scheduleDatabase[i].bandName, scheduleDatabase[i].date);
    }
}

// Ücret Hesaplama ve Gecikme Bildirimi
void calculateFare(const char* route, const char* ticketType) {
    double baseFare = 5.0;
    if (strcmp(ticketType, "Student") == 0) {
        baseFare *= 0.5;
    }
    printf("Calculated fare for %s with %s ticket: %.2f\n", route, ticketType, baseFare);
}

void alertForDelays() {
    printf("No delays currently reported.\n");
}

// Veriyi Sıkıştırma ve Açma (Örnek işlevler)
void compressAndSaveData(const char* data) {
    printf("Data compressed and saved.\n");
}

char* decompressData() {
    return "Decompressed data.";
}

// Ticket Sales Tracking İşlemleri
void loadSalesDatabase() {
    FILE* file;
    fopen_s(&file, "salesDatabase.bin", "rb");
    if (file) {
        fread(&salesCount, sizeof(int), 1, file);
        fread(salesDatabase, sizeof(TicketSale), salesCount, file);
        fclose(file);
    }
}

void saveSalesDatabase() {
    FILE* file;
    fopen_s(&file, "salesDatabase.bin", "wb");
    fwrite(&salesCount, sizeof(int), 1, file);
    fwrite(salesDatabase, sizeof(TicketSale), salesCount, file);
    fclose(file);
}

void viewSalesData() {
    loadSalesDatabase();
    printf("Ticket Sales Data:\n");
    for (int i = 0; i < salesCount; i++) {
        printf("ID: %d | Type: %s | Amount: %.2f | Date: %s\n",
            salesDatabase[i].saleID,
            salesDatabase[i].ticketType,
            salesDatabase[i].amount,
            salesDatabase[i].date);
    }
}

void generateSalesReport() {
    loadSalesDatabase();
    double totalAmount = 0.0;
    for (int i = 0; i < salesCount; i++) {
        totalAmount += salesDatabase[i].amount;
    }
    printf("Sales Report:\n");
    printf("Total Sales Count: %d\n", salesCount);
    printf("Total Sales Amount: %.2f\n", totalAmount);
}

// Vendor and Sponsor Coordination İşlemleri
void loadVendorDatabase() {
    FILE* file;
    fopen_s(&file, "vendorDatabase.bin", "rb");
    if (file) {
        fread(&vendorCount, sizeof(int), 1, file);
        fread(vendorDatabase, sizeof(Vendor), vendorCount, file);
        fclose(file);
    }
}

void saveVendorDatabase() {
    FILE* file;
    fopen_s(&file, "vendorDatabase.bin", "wb");
    fwrite(&vendorCount, sizeof(int), 1, file);
    fwrite(vendorDatabase, sizeof(Vendor), vendorCount, file);
    fclose(file);
}

void manageVendors() {
    loadVendorDatabase();
    printf("Vendors List:\n");
    for (int i = 0; i < vendorCount; i++) {
        printf("ID: %d | Name: %s | Service: %s\n",
            vendorDatabase[i].vendorID,
            vendorDatabase[i].name,
            vendorDatabase[i].serviceType);
    }
}

void loadSponsorDatabase() {
    FILE* file;
    fopen_s(&file, "sponsorDatabase.bin", "rb");
    if (file) {
        fread(&sponsorCount, sizeof(int), 1, file);
        fread(sponsorDatabase, sizeof(Sponsor), sponsorCount, file);
        fclose(file);
    }
}

void saveSponsorDatabase() {
    FILE* file;
    fopen_s(&file, "sponsorDatabase.bin", "wb");
    fwrite(&sponsorCount, sizeof(int), 1, file);
    fwrite(sponsorDatabase, sizeof(Sponsor), sponsorCount, file);
    fclose(file);
}

void trackSponsors() {
    loadSponsorDatabase();
    printf("Sponsors List:\n");
    for (int i = 0; i < sponsorCount; i++) {
        printf("ID: %d | Name: %s | Contribution: %.2f\n",
            sponsorDatabase[i].sponsorID,
            sponsorDatabase[i].name,
            sponsorDatabase[i].contributionAmount);
    }
}

// Double Linked List İşlevleri
void insertDoubleNode(DoubleNode** head, int data) {
    DoubleNode* newNode = (DoubleNode*)malloc(sizeof(DoubleNode));
    newNode->data = data;
    newNode->next = *head;
    newNode->prev = NULL;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void saveDoubleLinkedListToFile(DoubleNode* head, const char* filename) {
    FILE* file;
    fopen_s(&file, filename, "wb");
    if (file) {
        DoubleNode* current = head;
        while (current != NULL) {
            fwrite(&(current->data), sizeof(int), 1, file);
            current = current->next;
        }
        fclose(file);
    }
    else {
        printf("Error: Could not open file for writing linked list.\n");
    }
}

void loadDoubleLinkedListFromFile(DoubleNode** head, const char* filename) {
    FILE* file;
    fopen_s(&file, filename, "rb");
    if (file) {
        int data;
        while (fread(&data, sizeof(int), 1, file)) {
            insertDoubleNode(head, data);
        }
        fclose(file);
    }
    else {
        printf("Error: Could not open file for reading linked list.\n");
    }
}

// XOR Linked List İşlevleri
void saveXORLinkedListToFile(XORNode* head, const char* filename) {
    FILE* file;
    fopen_s(&file, filename, "wb");
    if (file) {
        XORNode* current = head;
        XORNode* prev = NULL;
        XORNode* next;
        while (current != NULL) {
            fwrite(&(current->data), sizeof(int), 1, file);
            next = XOR(prev, current->npx);
            prev = current;
            current = next;
        }
        fclose(file);
    }
    else {
        printf("Error: Could not open file for writing XOR linked list.\n");
    }
}

void loadXORLinkedListFromFile(XORNode** head, const char* filename) {
    FILE* file;
    fopen_s(&file, filename, "rb");
    if (file) {
        int data;
        while (fread(&data, sizeof(int), 1, file)) {
            insertXORNode(head, data);
        }
        fclose(file);
    }
    else {
        printf("Error: Could not open file for reading XOR linked list.\n");
    }
}

// Seyrek Matris İşlevleri
void saveSparseMatrixToFile(SparseMatrixNode* head, const char* filename) {
    FILE* file;
    fopen_s(&file, filename, "wb");
    if (file) {
        SparseMatrixNode* current = head;
        while (current != NULL) {
            fwrite(&(current->row), sizeof(int), 1, file);
            fwrite(&(current->col), sizeof(int), 1, file);
            fwrite(&(current->value), sizeof(int), 1, file);
            current = current->next;
        }
        fclose(file);
    }
    else {
        printf("Error: Could not open file for writing sparse matrix.\n");
    }
}

void loadSparseMatrixFromFile(SparseMatrixNode** head, const char* filename) {
    FILE* file;
    fopen_s(&file, filename, "rb");
    if (file) {
        int row, col, value;
        while (fread(&row, sizeof(int), 1, file) &&
            fread(&col, sizeof(int), 1, file) &&
            fread(&value, sizeof(int), 1, file)) {
            insertSparseNode(head, row, col, value);
        }
        fclose(file);
    }
    else {
        printf("Error: Could not open file for reading sparse matrix.\n");
    }
}

void insertXORNode(XORNode** head, int data) {
    XORNode* newNode = (XORNode*)malloc(sizeof(XORNode));
    newNode->data = data;
    newNode->npx = *head;

    if (*head != NULL) {
        (*head)->npx = XOR(newNode, (*head)->npx);
    }
    *head = newNode;
}

void insertSparseNode(SparseMatrixNode** head, int row, int col, int value) {
    SparseMatrixNode* newNode = (SparseMatrixNode*)malloc(sizeof(SparseMatrixNode));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = *head;
    *head = newNode;
}

