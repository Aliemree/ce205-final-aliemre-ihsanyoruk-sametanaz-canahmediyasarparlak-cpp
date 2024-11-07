#include "publictransportationscheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>  // for uintptr_t
#include <stdbool.h>
#include "../../publictransportationschedulerapp/header/publictransportationschedulerapp.h"

// Global Definitions
int userCount = 0;
User userDatabase[100];
int bandCount = 0;
Band bandDatabase[100];
int scheduleCount = 0;
ScheduleNode scheduleDatabase[100];
int salesCount = 0;
TicketSale salesDatabase[100];

Vendor vendorDatabase[100];
int vendorCount = 0;
Sponsor sponsorDatabase[100];
int sponsorCount = 0;
DoubleNode* routeListHead = NULL;


// Hash Table Definitions
#define TABLE_SIZE 100
User* hashTable[TABLE_SIZE];

typedef struct {
    int routeID;
    char routeName[50];
} Route;

// Hash Table Functions
int hashFunction(const char* key) {
    int hash = 0;
    while (*key) hash += *key++;
    return hash % TABLE_SIZE;
}

void initializeHashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        hashTable[i] = NULL;
    }
}

void addUserToHashTable(const char* username, const char* password) {
    int index = hashFunction(username);
    if (hashTable[index] == NULL) {
        hashTable[index] = (User*)malloc(sizeof(User));
        strcpy(hashTable[index]->username, username);
        strcpy(hashTable[index]->password, password);
    }
}

int verifyUserInHashTable(const char* username, const char* password) {
    int index = hashFunction(username);
    if (hashTable[index] != NULL && strcmp(hashTable[index]->username, username) == 0 &&
        strcmp(hashTable[index]->password, password) == 0) {
        return 1;
    }
    return 0;
}

// Double Linked List Functions
void addRoute(int routeID, const char* routeName, const char* startPoint, const char* endPoint) {
    DoubleNode* newNode = (DoubleNode*)malloc(sizeof(DoubleNode));
    newNode->data = routeID;
    strcpy(newNode->routeName, routeName);
    strcpy(newNode->startPoint, startPoint);
    strcpy(newNode->endPoint, endPoint);
    newNode->next = routeListHead;
    newNode->prev = NULL;

    if (routeListHead != NULL) {
        routeListHead->prev = newNode;
    }
    routeListHead = newNode;
}

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
// Route bulma
DoubleNode* findDoubleNode(DoubleNode* head, int data) {
    DoubleNode* current = head;
    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;  // Bulunamadı
}

// Route silme
int deleteDoubleNode(DoubleNode** head, int data) {
    DoubleNode* current = *head;

    while (current != NULL) {
        if (current->data == data) {
            if (current->prev) {
                current->prev->next = current->next;
            }
            else {
                *head = current->next;  // Baş düğüm siliniyor
            }
            if (current->next) {
                current->next->prev = current->prev;
            }
            free(current);
            return 1;  // Silme başarılı
        }
        current = current->next;
    }
    return 0;  // Route bulunamadı
}
void editRoute(DoubleNode* routeNode, const char* routeName, const char* startPoint, const char* endPoint) {
    if (routeNode != NULL) {
        strcpy(routeNode->routeName, routeName);
        strcpy(routeNode->startPoint, startPoint);
        strcpy(routeNode->endPoint, endPoint);
    }
}
void printDetailedRouteList(DoubleNode* head) {
    DoubleNode* current = head;
    printf("Current Routes:\n");
    while (current != NULL) {
        printf("Route ID: %d | Name: %s | Start: %s | End: %s\n",
            current->data, current->routeName, current->startPoint, current->endPoint);
        current = current->next;
    }
    if (head == NULL) {
        printf("No routes available.\n");
    }
}

void printDoubleList(DoubleNode* head) {
    DoubleNode* current = head;
    printf("Current Routes:\n");
    while (current != NULL) {
        printf("Route ID: %d\n", current->data);
        current = current->next;
    }
    if (head == NULL) {
        printf("No routes available.\n");
    }
}
// XOR Linked List Functions
XORNode* XOR(XORNode* a, XORNode* b) {
    return (XORNode*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

void insertXORNode(XORNode** head, int data) {
    XORNode* newNode = (XORNode*)malloc(sizeof(XORNode));
    newNode->data = data;
    newNode->npx = *head;
    if (*head != NULL) (*head)->npx = XOR(newNode, (*head)->npx);
    *head = newNode;
}

// Sparse Matrix Functions
void insertSparseNode(SparseMatrixNode** head, int row, int col, int value) {
    SparseMatrixNode* newNode = (SparseMatrixNode*)malloc(sizeof(SparseMatrixNode));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = *head;
    *head = newNode;
}

Node* stack = NULL;
Node* queueFront = NULL, * queueRear = NULL;

void push(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = stack;
    stack = newNode;
}

int pop() {
    if (!stack) return -1;
    int data = stack->data;
    Node* temp = stack;
    stack = stack->next;
    free(temp);
    return data;
}

void enqueue(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (queueRear) queueRear->next = newNode;
    queueRear = newNode;
    if (!queueFront) queueFront = newNode;
}

int dequeue() {
    if (!queueFront) return -1;
    int data = queueFront->data;
    Node* temp = queueFront;
    queueFront = queueFront->next;
    if (!queueFront) queueRear = NULL;
    free(temp);
    return data;
}

// Priority Queue (Heap)
int heap[100];
int heapSize = 0;

void insertHeap(int data) {
    int i = heapSize++;
    while (i && data < heap[(i - 1) / 2]) {
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i] = data;
}

int extractMin() {
    if (!heapSize) return -1;
    int root = heap[0];
    heap[0] = heap[--heapSize];
    int i = 0;
    while (2 * i + 1 < heapSize) {
        int left = 2 * i + 1, right = 2 * i + 2;
        int smallest = (right < heapSize && heap[right] < heap[left]) ? right : left;
        if (heap[i] <= heap[smallest]) break;
        int temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        i = smallest;
    }
    return root;
}

// BFS and DFS Functions
void bfs(int startNode) {
    enqueue(startNode);
    printf("BFS starting from node %d:\n", startNode);

    while (queueFront) {
        int currentNode = dequeue();
        printf("%d ", currentNode);
        // Bu noktada komşu düğümleri kuyruk yapısına ekleyebilirsiniz
    }
    printf("\n");
}

void dfs(int startNode) {
    push(startNode);
    printf("DFS starting from node %d:\n", startNode);

    while (stack) {
        int currentNode = pop();
        printf("%d ", currentNode);
        // Bu noktada komşu düğümleri yığına ekleyebilirsiniz
    }
    printf("\n");
}

// Huffman Coding Functions
void compressDataHuffman(const char* data) {
    printf("Data compressed using Huffman coding.\n");
    // Huffman kodlama algoritması burada uygulanabilir
}

void decompressDataHuffman() {
    printf("Data decompressed using Huffman coding.\n");
    // Huffman kodlama çözme algoritması burada uygulanabilir
}

// KMP Algorithm for text search
void KMPSearch(const char* pattern, const char* text) {
    int m = strlen(pattern);
    int n = strlen(text);
    int* lps = (int*)malloc(m * sizeof(int));  // Dinamik bellek tahsisi
    int j = 0;

    // LPS dizisini oluşturma
    lps[0] = 0;
    for (int i = 1; i < m;) {
        if (pattern[i] == pattern[j]) {
            lps[i++] = ++j;
        }
        else if (j) {
            j = lps[j - 1];
        }
        else {
            lps[i++] = 0;
        }
    }

    // Metin arama
    for (int i = 0; i < n;) {
        if (pattern[j] == text[i]) {
            ++j; ++i;
        }
        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i]) {
            j = j ? lps[j - 1] : 0;
        }
    }

    free(lps);  // Dinamik olarak tahsis edilen belleği serbest bırak
}

// User Authentication Functions
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
            printf("Login successful. Redirecting to main menu...\n");
            
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

    // Kayıt işleminden sonra otomatik olarak login fonksiyonunu çağır
    if (login(username, password)) {
        printf("Login successful. Redirecting to main menu...\n");
    }
    else {
        printf("Login failed after registration.\n");
    }
}


// Band and Artist Management Functions
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

// Schedule Management Functions



void editSchedule(int scheduleID, const char* newBandName, const char* newDate) {
    ScheduleNode* current = scheduleHead;
    while (current != NULL) {
        if (current->scheduleID == scheduleID) {
            strcpy(current->bandName, newBandName);
            strcpy(current->date, newDate);
            printf("Schedule %d updated to band %s on %s.\n", scheduleID, newBandName, newDate);
            return;
        }
        current = current->next;
    }
    printf("Schedule ID %d not found.\n", scheduleID);
}
void viewSchedules() {
    ScheduleNode* current = scheduleHead;
    printf("Festival Lineup:\n");
    while (current != NULL) {
        printf("ID: %d | Band: %s | Date: %s\n", current->scheduleID, current->bandName, current->date);
        current = current->next;
    }
    if (scheduleHead == NULL) {
        printf("No schedules available.\n");
    }
}
int deleteSchedule(int scheduleID) {
    ScheduleNode* current = scheduleHead;

    while (current != NULL) {
        if (current->scheduleID == scheduleID) {
            if (current->prev) {
                current->prev->next = current->next;
            }
            else {
                scheduleHead = current->next; // Baş düğüm siliniyor
            }
            if (current->next) {
                current->next->prev = current->prev;
            }
            free(current);
            printf("Schedule with ID %d deleted.\n", scheduleID);
            return 1;  // Silme başarılı
        }
        current = current->next;
    }
    printf("Schedule ID %d not found.\n", scheduleID);
    return 0;  // Program bulunamadı
}

void loadScheduleDatabase() {
    FILE* file;
    fopen_s(&file, "scheduleDatabase.bin", "rb");
    if (file) {
        int count;
        fread(&count, sizeof(int), 1, file);

        for (int i = 0; i < count; ++i) {
            int scheduleID;
            char bandName[50];
            char date[20];

            fread(&scheduleID, sizeof(int), 1, file);
            fread(bandName, sizeof(bandName), 1, file);
            fread(date, sizeof(date), 1, file);

            // Yeni programı listeye ekle
            createSchedule(scheduleID, bandName, date);
        }
        fclose(file);
    } else {
        printf("Error: Could not open file for reading.\n");
    }
}

void createSchedule(int scheduleID, const char* bandName, const char* date) {
    ScheduleNode* newNode = (ScheduleNode*)malloc(sizeof(ScheduleNode));
    newNode->scheduleID = scheduleID;
    strcpy(newNode->bandName, bandName);
    strcpy(newNode->date, date);
    newNode->next = scheduleHead;
    newNode->prev = NULL;

    if (scheduleHead != NULL) {
        scheduleHead->prev = newNode;
    }
    scheduleHead = newNode;
    printf("Schedule created for %s on %s.\n", bandName, date);
}

void saveScheduleDatabase() {
    FILE* file;
    fopen_s(&file, "scheduleDatabase.bin", "wb");
    if (file) {
        ScheduleNode* current = scheduleHead;
        int count = 0;

        // Düğümleri sayma
        while (current != NULL) {
            count++;
            current = current->next;
        }

        // Düğüm sayısını yazma
        fwrite(&count, sizeof(int), 1, file);

        // Program verilerini yazma
        current = scheduleHead;
        while (current != NULL) {
            fwrite(&(current->scheduleID), sizeof(int), 1, file);
            fwrite(current->bandName, sizeof(current->bandName), 1, file);
            fwrite(current->date, sizeof(current->date), 1, file);
            current = current->next;
        }
        fclose(file);
    }
    else {
        printf("Error: Could not open file for writing.\n");
    }
}


// Ticket Sales Tracking Functions
void loadSalesDatabase() {
    FILE* file;
    fopen_s(&file, "salesDatabase.bin", "rb");
    if (file) {
        fread(&salesCount, sizeof(int), 1, file);
        fread(salesDatabase, sizeof(TicketSale), salesCount, file);
        fclose(file);
        printf("Sales database loaded successfully.\n");
    }
    else {
        printf("No existing sales database found.\n");
    }
}

void saveSalesDatabase() {
    FILE* file;
    fopen_s(&file, "salesDatabase.bin", "wb");
    if (file) {
        fwrite(&salesCount, sizeof(int), 1, file);
        fwrite(salesDatabase, sizeof(TicketSale), salesCount, file);
        fclose(file);
        printf("Sales database saved successfully.\n");
    }
    else {
        printf("Failed to save sales database.\n");
    }
}

void viewSalesData() {
    printf("Ticket Sales Data:\n");
    for (int i = 0; i < salesCount; i++) {
        printf("Sale ID: %d, Type: %s, Amount: %.2f, Date: %s\n",
            salesDatabase[i].saleID,
            salesDatabase[i].ticketType,
            salesDatabase[i].amount,
            salesDatabase[i].date);
    }
    if (salesCount == 0) {
        printf("No sales data available.\n");
    }
}

void generateSalesReport() {
    double totalAmount = 0.0;
    int normalCount = 0, studentCount = 0;

    for (int i = 0; i < salesCount; i++) {
        totalAmount += salesDatabase[i].amount;
        if (strcmp(salesDatabase[i].ticketType, "Normal") == 0) {
            normalCount++;
        }
        else if (strcmp(salesDatabase[i].ticketType, "Student") == 0) {
            studentCount++;
        }
    }

    printf("Sales Report:\n");
    printf("Total Sales Amount: %.2f\n", totalAmount);
    printf("Total 'Normal' Tickets Sold: %d\n", normalCount);
    printf("Total 'Student' Tickets Sold: %d\n", studentCount);
    printf("Total Sales Count: %d\n", salesCount);
}

// Vendor ekleme fonksiyonu
void addVendor(int id, const char* name, const char* serviceType) {
    Vendor* newVendor = (Vendor*)malloc(sizeof(Vendor));
    newVendor->id = id;
    strcpy(newVendor->name, name);
    strcpy(newVendor->serviceType, serviceType);
    newVendor->next = vendorListHead;
    vendorListHead = newVendor;
}

// Sponsor ekleme fonksiyonu
void addSponsor(int id, const char* name, double contributionAmount) {
    Sponsor* newSponsor = (Sponsor*)malloc(sizeof(Sponsor));
    newSponsor->id = id;
    strcpy(newSponsor->name, name);
    newSponsor->contributionAmount = contributionAmount;
    newSponsor->next = sponsorListHead;
    sponsorListHead = newSponsor;
}

// Vendor veritabanını kaydetme fonksiyonu
void saveVendorDatabase() {
    FILE* file;
    fopen_s(&file, "vendorDatabase.bin", "wb");
    Vendor* current = vendorListHead;
    while (current != NULL) {
        fwrite(current, sizeof(Vendor), 1, file);
        current = current->next;
    }
    fclose(file);
}

// Sponsor veritabanını kaydetme fonksiyonu
void saveSponsorDatabase() {
    FILE* file;
    fopen_s(&file, "sponsorDatabase.bin", "wb");
    Sponsor* current = sponsorListHead;
    while (current != NULL) {
        fwrite(current, sizeof(Sponsor), 1, file);
        current = current->next;
    }
    fclose(file);
}

// Vendor veritabanını yükleme fonksiyonu
void loadVendorDatabase() {
    FILE* file;
    fopen_s(&file, "vendorDatabase.bin", "rb");
    if (file) {
        Vendor temp;
        while (fread(&temp, sizeof(Vendor), 1, file)) {
            addVendor(temp.id, temp.name, temp.serviceType);
        }
        fclose(file);
    }
}

// Sponsor veritabanını yükleme fonksiyonu
void loadSponsorDatabase() {
    FILE* file;
    fopen_s(&file, "sponsorDatabase.bin", "rb");
    if (file) {
        Sponsor temp;
        while (fread(&temp, sizeof(Sponsor), 1, file)) {
            addSponsor(temp.id, temp.name, temp.contributionAmount);
        }
        fclose(file);
    }
}

// Vendor ekleme işlemi
void addVendorMenu() {
    int id;
    char name[50];
    char serviceType[50];
    printf("Enter Vendor ID: ");
    scanf("%d", &id);
    printf("Enter Vendor Name: ");
    scanf("%s", name);
    printf("Enter Service Type: ");
    scanf("%s", serviceType);
    addVendor(id, name, serviceType);
    saveVendorDatabase();
    printf("Vendor added and saved successfully.\n");
}

// Sponsor ekleme işlemi
void addSponsorMenu() {
    int id;
    char name[50];
    double contributionAmount;
    printf("Enter Sponsor ID: ");
    scanf("%d", &id);
    printf("Enter Sponsor Name: ");
    scanf("%s", name);
    printf("Enter Contribution Amount: ");
    scanf("%lf", &contributionAmount);
    addSponsor(id, name, contributionAmount);
    saveSponsorDatabase();
    printf("Sponsor added and saved successfully.\n");
}

// Vendor listeleme
void manageVendors() {
    loadVendorDatabase();  // Güncel veriyi yükle
    Vendor* current = vendorListHead;
    printf("Vendors List:\n");
    while (current != NULL) {
        printf("ID: %d | Name: %s | Service: %s\n", current->id, current->name, current->serviceType);
        current = current->next;
    }
}

// Sponsor listeleme
void trackSponsors() {
    loadSponsorDatabase();  // Güncel veriyi yükle
    Sponsor* current = sponsorListHead;
    printf("Sponsors List:\n");
    while (current != NULL) {
        printf("ID: %d | Name: %s | Contribution: %.2f\n", current->id, current->name, current->contributionAmount);
        current = current->next;
    }
}