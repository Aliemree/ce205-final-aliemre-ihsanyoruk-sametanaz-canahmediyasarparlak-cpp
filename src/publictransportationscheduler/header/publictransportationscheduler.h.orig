#ifndef PUBLICTRANSPORTATIONSCHEDULER_H
#define PUBLICTRANSPORTATIONSCHEDULER_H

#include <stdint.h>
#include <stdbool.h>  // B+ ağacı için gerekli olabilir



// User structure
typedef struct {
  char username[50];
  char password[50];
} User;

// Band structure
typedef struct {
  char name[50];
} Band;

// Schedule structure
typedef struct ScheduleNode {
  int scheduleID;
  char bandName[50];
  char date[20];
  struct ScheduleNode *next;
  struct ScheduleNode *prev;
} ScheduleNode;

ScheduleNode *scheduleHead = NULL;

// Ticket Sale structure (Tek tanımlama)
typedef struct {
  int saleID;
  char ticketType[20];
  float amount;
  char date[20];
} TicketSale;

typedef struct Vendor {
  int id;
  char name[50];
  char serviceType[50];
  struct Vendor *next;
} Vendor;

typedef struct Sponsor {
  int id;
  char name[50];
  double contributionAmount;
  struct Sponsor *next;
} Sponsor;

// Global vendor ve sponsor listeleri
Vendor *vendorListHead = NULL;
Sponsor *sponsorListHead = NULL;

// Double Linked List Node
typedef struct DoubleNode {
  int data; // Route ID
  char routeName[50]; // Route Name
  char startPoint[50]; // Starting Point
  char endPoint[50]; // Ending Point
  struct DoubleNode *next;
  struct DoubleNode *prev;
} DoubleNode;

// XOR Linked List Node
typedef struct XORNode {
  int data;
  struct XORNode *npx;  // XOR of next and previous node
} XORNode;

// Sparse Matrix Node
typedef struct SparseMatrixNode {
  int row;
  int col;
  int value;
  struct SparseMatrixNode *next;
} SparseMatrixNode;

// Stack and Queue Node
typedef struct Node {
  int data;
  struct Node *next;
} Node;

// B+ Ağacı düğüm yapısı
#define MAX_KEYS 4

typedef struct BPlusTreeNode {
  int keys[MAX_KEYS];
  TicketSale *sales[MAX_KEYS];
  struct BPlusTreeNode *children[MAX_KEYS + 1];
  int numKeys;
  bool isLeaf;
  struct BPlusTreeNode *next;  // Yaprak düğümler için bağlantı
} BPlusTreeNode;

BPlusTreeNode *root = NULL;  // B+ Ağacının kök düğümü

// Function prototypes
void initializeHashTable();
int hashFunction(const char *key);
void addUserToHashTable(const char *username, const char *password);
int verifyUserInHashTable(const char *username, const char *password);

void insertDoubleNode(DoubleNode **head, int data);
void printDoubleList(DoubleNode *head);

XORNode *XOR(XORNode *a, XORNode *b);
void insertXORNode(XORNode **head, int data);

void insertSparseNode(SparseMatrixNode **head, int row, int col, int value);

void push(int data);
int pop();
void enqueue(int data);
int dequeue();

void insertHeap(int data);
int extractMin();

void bfs(int startNode);
void dfs(int startNode);

void compressDataHuffman(const char *data);
void decompressDataHuffman();

void KMPSearch(const char *pattern, const char *text);

void loadUserDatabase();
void saveUserDatabase();
int login(const char *username, const char *password);
void registerUser(const char *username, const char *password);

void loadBandDatabase();
void saveBandDatabase();
void addBand(const char *name);
void editBand(const char *oldName, const char *newName);
void viewBands();

void loadScheduleDatabase();
void saveScheduleDatabase();
void createSchedule(int scheduleID, const char *bandName, const char *date);
void viewSchedules();

void loadSalesDatabase();
void saveSalesDatabase();
void viewSalesData();
void generateSalesReport();

// B+ ağacı fonksiyon prototipleri
void insertBPlusNode(int key, TicketSale *sale);
void displayBPlusTree(BPlusTreeNode *node);
TicketSale *searchBPlusTree(int key);
void initializeBPlusTree();

void loadVendorDatabase();
void saveVendorDatabase();
void manageVendors();
void addSponsorMenu();
void addVendorMenu();

void loadSponsorDatabase();
void saveSponsorDatabase();
void trackSponsors();

// Double Linked List Functions
void insertDoubleNode(DoubleNode **head, int data);
DoubleNode *findDoubleNode(DoubleNode *head, int data);
int deleteDoubleNode(DoubleNode **head, int data);
void printDoubleList(DoubleNode *head);

#endif // PUBLICTRANSPORTATIONSCHEDULER_H