#include "publictransportationscheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // for uintptr_t

// User, band, and schedule database definitions
int userCount = 0;
User userDatabase[100];

int bandCount = 0;
Band bandDatabase[100];

int scheduleCount = 0;
Schedule scheduleDatabase[100];

// Ticket sales database
TicketSale salesDatabase[100];
int salesCount = 0;

// Vendor database
Vendor vendorDatabase[100];
int vendorCount = 0;

// Sponsor database
Sponsor sponsorDatabase[100];
int sponsorCount = 0;

// XOR function for XOR linked list nodes
/**
 * XORs two pointers to create a single XORed pointer.
 * @param a First pointer
 * @param b Second pointer
 * @return XORed pointer result
 */
XORNode* XOR(XORNode* a, XORNode* b) {
    return (XORNode*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

// User Authentication Functions
/**
 * Loads the user database from a binary file.
 */
void loadUserDatabase() {
    FILE* file;
    fopen_s(&file, "userDatabase.bin", "rb");
    if (file) {
        fread(&userCount, sizeof(int), 1, file);
        fread(userDatabase, sizeof(User), userCount, file);
        fclose(file);
    }
}

/**
 * Saves the user database to a binary file.
 */
void saveUserDatabase() {
    FILE* file;
    fopen_s(&file, "userDatabase.bin", "wb");
    fwrite(&userCount, sizeof(int), 1, file);
    fwrite(userDatabase, sizeof(User), userCount, file);
    fclose(file);
}

/**
 * Authenticates a user by verifying their username and password.
 * @param username The username to authenticate
 * @param password The password to authenticate
 * @return 1 if login is successful, 0 otherwise
 */
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

/**
 * Registers a new user by adding them to the user database.
 * @param username The username for the new user
 * @param password The password for the new user
 */
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

/**
 * Activates guest mode with limited access.
 */
void activateGuestMode() {
    printf("Guest Mode activated. Limited access granted.\n");
}

// Band and Artist Management Functions
/**
 * Loads the band database from a binary file.
 */
void loadBandDatabase() {
    FILE* file;
    fopen_s(&file, "bandDatabase.bin", "rb");
    if (file) {
        fread(&bandCount, sizeof(int), 1, file);
        fread(bandDatabase, sizeof(Band), bandCount, file);
        fclose(file);
    }
}

/**
 * Saves the band database to a binary file.
 */
void saveBandDatabase() {
    FILE* file;
    fopen_s(&file, "bandDatabase.bin", "wb");
    fwrite(&bandCount, sizeof(int), 1, file);
    fwrite(bandDatabase, sizeof(Band), bandCount, file);
    fclose(file);
}

/**
 * Adds a new band or artist to the band database.
 * @param name The name of the band or artist
 */
void addBand(const char* name) {
    loadBandDatabase();
    strcpy_s(bandDatabase[bandCount].name, sizeof(bandDatabase[bandCount].name), name);
    bandCount++;
    saveBandDatabase();
    printf("Band/Artist %s added.\n", name);
}

/**
 * Edits the name of an existing band or artist.
 * @param oldName The current name of the band or artist
 * @param newName The new name for the band or artist
 */
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

/**
 * Displays the list of bands and artists.
 */
void viewBands() {
    loadBandDatabase();
    printf("Band and Artist List:\n");
    for (int i = 0; i < bandCount; i++) {
        printf("%s\n", bandDatabase[i].name);
    }
}

// Schedule Management Functions
/**
 * Loads the schedule database from a binary file.
 */
void loadScheduleDatabase() {
    FILE* file;
    fopen_s(&file, "scheduleDatabase.bin", "rb");
    if (file) {
        fread(&scheduleCount, sizeof(int), 1, file);
        fread(scheduleDatabase, sizeof(Schedule), scheduleCount, file);
        fclose(file);
    }
}

/**
 * Saves the schedule database to a binary file.
 */
void saveScheduleDatabase() {
    FILE* file;
    fopen_s(&file, "scheduleDatabase.bin", "wb");
    fwrite(&scheduleCount, sizeof(int), 1, file);
    fwrite(scheduleDatabase, sizeof(Schedule), scheduleCount, file);
    fclose(file);
}

/**
 * Creates a new schedule entry for a band or artist.
 * @param scheduleID The unique ID for the schedule entry
 * @param bandName The name of the band or artist in the schedule
 * @param date The date of the scheduled performance
 */
void createSchedule(int scheduleID, const char* bandName, const char* date) {
    loadScheduleDatabase();
    scheduleDatabase[scheduleCount].scheduleID = scheduleID;
    strcpy_s(scheduleDatabase[scheduleCount].bandName, sizeof(scheduleDatabase[scheduleCount].bandName), bandName);
    strcpy_s(scheduleDatabase[scheduleCount].date, sizeof(scheduleDatabase[scheduleCount].date), date);
    scheduleCount++;
    saveScheduleDatabase();
    printf("Schedule created for band %s on %s.\n", bandName, date);
}

/**
 * Edits an existing schedule entry.
 * @param scheduleID The unique ID of the schedule entry to edit
 * @param newBandName The new band or artist name for the schedule
 * @param newDate The new date for the scheduled performance
 */
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

/**
 * Displays the festival lineup with scheduled performances.
 */
void viewSchedules() {
    loadScheduleDatabase();
    printf("Festival Lineup:\n");
    for (int i = 0; i < scheduleCount; i++) {
        printf("ID: %d | Band: %s | Date: %s\n", scheduleDatabase[i].scheduleID, scheduleDatabase[i].bandName, scheduleDatabase[i].date);
    }
}

// Fare Calculation and Delay Notification Functions
/**
 * Calculates the fare based on route and ticket type.
 * @param route The route for fare calculation
 * @param ticketType The type of ticket (e.g., "Student", "Regular")
 */
void calculateFare(const char* route, const char* ticketType) {
    double baseFare = 5.0;
    if (strcmp(ticketType, "Student") == 0) {
        baseFare *= 0.5;
    }
    printf("Calculated fare for %s with %s ticket: %.2f\n", route, ticketType, baseFare);
}

/**
 * Alerts for any current delays.
 */
void alertForDelays() {
    printf("No delays currently reported.\n");
}

// Data Compression and Decompression Functions (Example functions)
/**
 * Compresses data and saves it to a file (example function).
 * @param data The data to be compressed and saved
 */
void compressAndSaveData(const char* data) {
    printf("Data compressed and saved.\n");
}

/**
 * Decompresses data from a file (example function).
 * @return The decompressed data as a string
 */
char* decompressData() {
    return "Decompressed data.";
}

// Ticket Sales Tracking Functions
/**
 * Loads the ticket sales database from a binary file.
 */
void loadSalesDatabase() {
    FILE* file;
    fopen_s(&file, "salesDatabase.bin", "rb");
    if (file) {
        fread(&salesCount, sizeof(int), 1, file);
        fread(salesDatabase, sizeof(TicketSale), salesCount, file);
        fclose(file);
    }
}

/**
 * Saves the ticket sales database to a binary file.
 */
void saveSalesDatabase() {
    FILE* file;
    fopen_s(&file, "salesDatabase.bin", "wb");
    fwrite(&salesCount, sizeof(int), 1, file);
    fwrite(salesDatabase, sizeof(TicketSale), salesCount, file);
    fclose(file);
}

/**
 * Displays ticket sales data.
 */
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

/**
 * Generates a sales report summarizing total sales.
 */
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

// Vendor and Sponsor Coordination Functions
/**
 * Loads the vendor database from a binary file.
 */
void loadVendorDatabase() {
    FILE* file;
    fopen_s(&file, "vendorDatabase.bin", "rb");
    if (file) {
        fread(&vendorCount, sizeof(int), 1, file);
        fread(vendorDatabase, sizeof(Vendor), vendorCount, file);
        fclose(file);
    }
}

/**
 * Saves the vendor database to a binary file.
 */
void saveVendorDatabase() {
    FILE* file;
    fopen_s(&file, "vendorDatabase.bin", "wb");
    fwrite(&vendorCount, sizeof(int), 1, file);
    fwrite(vendorDatabase, sizeof(Vendor), vendorCount, file);
    fclose(file);
}

/**
 * Manages and displays the list of vendors.
 */
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

/**
 * Loads the sponsor database from a binary file.
 */
void loadSponsorDatabase() {
    FILE* file;
    fopen_s(&file, "sponsorDatabase.bin", "rb");
    if (file) {
        fread(&sponsorCount, sizeof(int), 1, file);
        fread(sponsorDatabase, sizeof(Sponsor), sponsorCount, file);
        fclose(file);
    }
}

/**
 * Saves the sponsor database to a binary file.
 */
void saveSponsorDatabase() {
    FILE* file;
    fopen_s(&file, "sponsorDatabase.bin", "wb");
    fwrite(&sponsorCount, sizeof(int), 1, file);
    fwrite(sponsorDatabase, sizeof(Sponsor), sponsorCount, file);
    fclose(file);
}

/**
 * Tracks and displays the list of sponsors.
 */
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

// Double Linked List Functions
/**
 * Inserts a new node at the beginning of a double linked list.
 * @param head The head pointer of the double linked list
 * @param data The data to insert in the new node
 */
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

/**
 * Saves a double linked list to a binary file.
 * @param head The head of the double linked list
 * @param filename The file to save the list
 */
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

/**
 * Loads a double linked list from a binary file.
 * @param head The head pointer of the double linked list
 * @param filename The file to load the list from
 */
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

// XOR Linked List Functions
/**
 * Saves an XOR linked list to a binary file.
 * @param head The head of the XOR linked list
 * @param filename The file to save the list
 */
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

/**
 * Loads an XOR linked list from a binary file.
 * @param head The head pointer of the XOR linked list
 * @param filename The file to load the list from
 */
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

// Sparse Matrix Functions
/**
 * Saves a sparse matrix to a binary file.
 * @param head The head of the sparse matrix
 * @param filename The file to save the matrix
 */
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

/**
 * Loads a sparse matrix from a binary file.
 * @param head The head pointer of the sparse matrix
 * @param filename The file to load the matrix from
 */
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

/**
 * Inserts a new node into an XOR linked list.
 * @param head The head pointer of the XOR linked list
 * @param data The data to insert in the new node
 */
void insertXORNode(XORNode** head, int data) {
    XORNode* newNode = (XORNode*)malloc(sizeof(XORNode));
    newNode->data = data;
    newNode->npx = *head;

    if (*head != NULL) {
        (*head)->npx = XOR(newNode, (*head)->npx);
    }
    *head = newNode;
}

/**
 * Inserts a new node into a sparse matrix.
 * @param head The head pointer of the sparse matrix
 * @param row The row index of the matrix node
 * @param col The column index of the matrix node
 * @param value The value to insert in the matrix node
 */
void insertSparseNode(SparseMatrixNode** head, int row, int col, int value) {
    SparseMatrixNode* newNode = (SparseMatrixNode*)malloc(sizeof(SparseMatrixNode));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = *head;
    *head = newNode;
}
