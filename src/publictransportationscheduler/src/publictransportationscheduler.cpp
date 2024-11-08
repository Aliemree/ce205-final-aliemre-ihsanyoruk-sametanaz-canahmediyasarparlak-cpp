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
DoubleNode *routeListHead = NULL;


// Hash Table Definitions
#define TABLE_SIZE 100
User *hashTable[TABLE_SIZE];

typedef struct {
  int routeID;
  char routeName[50];
} Route;

/**
 * @brief Calculates the hash for a given key.
 * @param key The key to hash.
 * @return The hash index for the given key.
 */
int hashFunction(const char *key) {
  int hash = 0;

  while (*key) hash += *key++;

  return hash % TABLE_SIZE;
}

/**
 * @brief Initializes the hash table.
 */
void initializeHashTable() {
  for (int i = 0; i < TABLE_SIZE; ++i) {
    hashTable[i] = NULL;
  }
}

/**
 * @brief Adds a user to the hash table.
 * @param username The username to add.
 * @param password The password for the user.
 */
void addUserToHashTable(const char *username, const char *password) {
  int index = hashFunction(username);

  if (hashTable[index] == NULL) {
    hashTable[index] = (User *)malloc(sizeof(User));
    strcpy(hashTable[index]->username, username);
    strcpy(hashTable[index]->password, password);
  }
}

/**
 * @brief Verifies a user in the hash table.
 * @param username The username to verify.
 * @param password The password to verify.
 * @return 1 if the user is found and password matches, 0 otherwise.
 */
int verifyUserInHashTable(const char *username, const char *password) {
  int index = hashFunction(username);

  if (hashTable[index] != NULL && strcmp(hashTable[index]->username, username) == 0 &&
      strcmp(hashTable[index]->password, password) == 0) {
    return 1;
  }

  return 0;
}

// Double Linked List Functions

/**
 * @brief Adds a route to the double linked list.
 * @param routeID The route ID.
 * @param routeName The name of the route.
 * @param startPoint The starting point of the route.
 * @param endPoint The ending point of the route.
 */
void addRoute(int routeID, const char *routeName, const char *startPoint, const char *endPoint) {
  DoubleNode *newNode = (DoubleNode *)malloc(sizeof(DoubleNode));
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

/**
 * @brief Inserts a node into the double linked list.
 * @param head Pointer to the head of the list.
 * @param data The data to insert.
 */
void insertDoubleNode(DoubleNode **head, int data) {
  DoubleNode *newNode = (DoubleNode *)malloc(sizeof(DoubleNode));
  newNode->data = data;
  newNode->next = *head;
  newNode->prev = NULL;

  if (*head != NULL) {
    (*head)->prev = newNode;
  }

  *head = newNode;
}

/**
 * @brief Finds a route node by route ID in the double linked list.
 * @param head The head of the list.
 * @param data The route ID to search for.
 * @return Pointer to the node if found, NULL otherwise.
 */
DoubleNode *findDoubleNode(DoubleNode *head, int data) {
  DoubleNode *current = head;

  while (current != NULL) {
    if (current->data == data) {
      return current;
    }

    current = current->next;
  }

  return NULL;  // Not found
}

/**
 * @brief Deletes a node by route ID from the double linked list.
 * @param head Pointer to the head of the list.
 * @param data The route ID to delete.
 * @return 1 if the node is deleted, 0 if not found.
 */
int deleteDoubleNode(DoubleNode **head, int data) {
  DoubleNode *current = *head;

  while (current != NULL) {
    if (current->data == data) {
      if (current->prev) {
        current->prev->next = current->next;
      } else {
        *head = current->next;  // Head node is deleted
      }

      if (current->next) {
        current->next->prev = current->prev;
      }

      free(current);
      return 1;  // Deletion successful
    }

    current = current->next;
  }

  return 0;  // Route not found
}

/**
 * @brief Edits a route node with new details.
 * @param routeNode The node to edit.
 * @param routeName The new route name.
 * @param startPoint The new starting point.
 * @param endPoint The new ending point.
 */
void editRoute(DoubleNode *routeNode, const char *routeName, const char *startPoint, const char *endPoint) {
  if (routeNode != NULL) {
    strcpy(routeNode->routeName, routeName);
    strcpy(routeNode->startPoint, startPoint);
    strcpy(routeNode->endPoint, endPoint);
  }
}

/**
 * @brief Prints a detailed list of all routes.
 * @param head The head of the route list.
 */
void printDetailedRouteList(DoubleNode *head) {
  DoubleNode *current = head;
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

/**
 * @brief Prints a list of all routes by ID.
 * @param head The head of the route list.
 */
void printDoubleList(DoubleNode *head) {
  DoubleNode *current = head;
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

/**
 * @brief Computes the XOR of two pointers for XOR linked list.
 * @param a Pointer to the first XORNode.
 * @param b Pointer to the second XORNode.
 * @return XOR of the two pointers.
 */
XORNode *XOR(XORNode *a, XORNode *b) {
  return (XORNode *)((uintptr_t)(a) ^ (uintptr_t)(b));
}

/**
 * @brief Inserts a new node into the XOR linked list.
 * @param head Pointer to the head of the XOR linked list.
 * @param data Data to store in the new node.
 */
void insertXORNode(XORNode **head, int data) {
  XORNode *newNode = (XORNode *)malloc(sizeof(XORNode));
  newNode->data = data;
  newNode->npx = *head;

  if (*head != NULL) (*head)->npx = XOR(newNode, (*head)->npx);

  *head = newNode;
}

// Sparse Matrix Functions

/**
 * @brief Inserts a node into a sparse matrix linked list.
 * @param head Pointer to the head of the sparse matrix linked list.
 * @param row Row index of the value.
 * @param col Column index of the value.
 * @param value The value to insert.
 */
void insertSparseNode(SparseMatrixNode **head, int row, int col, int value) {
  SparseMatrixNode *newNode = (SparseMatrixNode *)malloc(sizeof(SparseMatrixNode));
  newNode->row = row;
  newNode->col = col;
  newNode->value = value;
  newNode->next = *head;
  *head = newNode;
}

// Stack and Queue Implementations

Node *stack = NULL;
Node *queueFront = NULL, *queueRear = NULL;

/**
 * @brief Pushes a data element onto the stack.
 * @param data The data to push onto the stack.
 */
void push(int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = stack;
  stack = newNode;
}

/**
 * @brief Pops a data element from the stack.
 * @return The popped data from the stack, or -1 if stack is empty.
 */
int pop() {
  if (!stack) return -1;

  int data = stack->data;
  Node *temp = stack;
  stack = stack->next;
  free(temp);
  return data;
}

/**
 * @brief Enqueues a data element into the queue.
 * @param data The data to enqueue.
 */
void enqueue(int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;

  if (queueRear) queueRear->next = newNode;

  queueRear = newNode;

  if (!queueFront) queueFront = newNode;
}

/**
 * @brief Dequeues a data element from the queue.
 * @return The dequeued data from the queue, or -1 if queue is empty.
 */
int dequeue() {
  if (!queueFront) return -1;

  int data = queueFront->data;
  Node *temp = queueFront;
  queueFront = queueFront->next;

  if (!queueFront) queueRear = NULL;

  free(temp);
  return data;
}

// Priority Queue (Heap) Implementation

int heap[100];
int heapSize = 0;

/**
 * @brief Inserts data into a min-heap.
 * @param data The data to insert into the heap.
 */
void insertHeap(int data) {
  int i = heapSize++;

  while (i && data < heap[(i - 1) / 2]) {
    heap[i] = heap[(i - 1) / 2];
    i = (i - 1) / 2;
  }

  heap[i] = data;
}

/**
 * @brief Extracts the minimum element from the min-heap.
 * @return The minimum element from the heap, or -1 if heap is empty.
 */
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

/**
 * @brief Performs Breadth-First Search (BFS) starting from a given node.
 * @param startNode The starting node for BFS.
 */
void bfs(int startNode) {
  enqueue(startNode);
  printf("BFS starting from node %d:\n", startNode);

  while (queueFront) {
    int currentNode = dequeue();
    printf("%d ", currentNode);
    // Komşu düğümleri kuyruk yapısına ekleyebilirsiniz
  }

  printf("\n");
}

/**
 * @brief Performs Depth-First Search (DFS) starting from a given node.
 * @param startNode The starting node for DFS.
 */
void dfs(int startNode) {
  push(startNode);
  printf("DFS starting from node %d:\n", startNode);

  while (stack) {
    int currentNode = pop();
    printf("%d ", currentNode);
    // Komşu düğümleri yığına ekleyebilirsiniz
  }

  printf("\n");
}
// Huffman Coding Functions

/**
 * @brief Compresses the given data using Huffman coding.
 * @param data The data to compress.
 */
void compressDataHuffman(const char *data) {
  printf("Data compressed using Huffman coding.\n");
  // Huffman encoding algorithm implementation can be added here.
}

/**
 * @brief Decompresses data using Huffman coding.
 */
void decompressDataHuffman() {
  printf("Data decompressed using Huffman coding.\n");
  // Huffman decoding algorithm implementation can be added here.
}

// KMP Algorithm for text search

/**
 * @brief Searches for a pattern within a text using the KMP algorithm.
 * @param pattern The pattern to search for.
 * @param text The text to search within.
 */
void KMPSearch(const char *pattern, const char *text) {
  int m = strlen(pattern);
  int n = strlen(text);
  int *lps = (int *)malloc(m * sizeof(int)); // Allocate memory for LPS array
  int j = 0;
  // Compute LPS array for the pattern
  lps[0] = 0;

  for (int i = 1; i < m;) {
    if (pattern[i] == pattern[j]) {
      lps[i++] = ++j;
    } else if (j) {
      j = lps[j - 1];
    } else {
      lps[i++] = 0;
    }
  }

  // Search for the pattern in the text
  for (int i = 0; i < n;) {
    if (pattern[j] == text[i]) {
      ++j;
      ++i;
    }

    if (j == m) {
      printf("Pattern found at index %d\n", i - j);
      j = lps[j - 1];
    } else if (i < n && pattern[j] != text[i]) {
      j = j ? lps[j - 1] : 0;
    }
  }

  free(lps);  // Free the dynamically allocated memory
}

// User Authentication Functions

/**
 * @brief Loads the user database from a binary file.
 */
void loadUserDatabase() {
  FILE *file;
  fopen_s(&file, "userDatabase.bin", "rb");

  if (file) {
    fread(&userCount, sizeof(int), 1, file);
    fread(userDatabase, sizeof(User), userCount, file);
    fclose(file);
  }
}

/**
 * @brief Saves the user database to a binary file.
 */
void saveUserDatabase() {
  FILE *file;
  fopen_s(&file, "userDatabase.bin", "wb");
  fwrite(&userCount, sizeof(int), 1, file);
  fwrite(userDatabase, sizeof(User), userCount, file);
  fclose(file);
}

/**
 * @brief Authenticates a user by verifying their username and password.
 * @param username The username to authenticate.
 * @param password The password associated with the username.
 * @return Returns 1 if login is successful, 0 otherwise.
 */
int login(const char *username, const char *password) {
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

/**
 * @brief Registers a new user with a username and password.
 * @param username The new user's username.
 * @param password The new user's password.
 */
void registerUser(const char *username, const char *password) {
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

  // Automatically log in after successful registration
  if (login(username, password)) {
    printf("Login successful. Redirecting to main menu...\n");
  } else {
    printf("Login failed after registration.\n");
  }
}

// Band and Artist Management Functions

/**
 * @brief Loads the band database from a binary file.
 */
void loadBandDatabase() {
  FILE *file;
  fopen_s(&file, "bandDatabase.bin", "rb");

  if (file) {
    fread(&bandCount, sizeof(int), 1, file);
    fread(bandDatabase, sizeof(Band), bandCount, file);
    fclose(file);
  }
}

/**
 * @brief Saves the band database to a binary file.
 */
void saveBandDatabase() {
  FILE *file;
  fopen_s(&file, "bandDatabase.bin", "wb");
  fwrite(&bandCount, sizeof(int), 1, file);
  fwrite(bandDatabase, sizeof(Band), bandCount, file);
  fclose(file);
}

/**
 * @brief Adds a new band or artist to the band database.
 * @param name The name of the band or artist to add.
 */
void addBand(const char *name) {
  loadBandDatabase();
  strcpy_s(bandDatabase[bandCount].name, sizeof(bandDatabase[bandCount].name), name);
  bandCount++;
  saveBandDatabase();
  printf("Band/Artist %s added.\n", name);
}

/**
 * @brief Edits the name of an existing band or artist.
 * @param oldName The current name of the band or artist.
 * @param newName The new name for the band or artist.
 */
void editBand(const char *oldName, const char *newName) {
  for (int i = 0; i < bandCount; i++) {
    if (strcmp(bandDatabase[i].name, oldName) == 0) {
      // Güncellenen adı bandDatabase dizisine kaydet
      strcpy(bandDatabase[i].name, newName);
      printf("Band/Artist %s updated to %s.\n", oldName, newName);
      return;
    }
  }

  printf("Band/Artist %s not found.\n", oldName);
}
/**
 * @brief Displays the list of all bands and artists.
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
 * @brief Edits an existing schedule with a new band and date.
 * @param scheduleID The ID of the schedule to edit.
 * @param newBandName The new band name.
 * @param newDate The new date for the schedule.
 */
void editSchedule(int scheduleID, const char *newBandName, const char *newDate) {
  ScheduleNode *current = scheduleHead;

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

/**
 * @brief Views all available schedules.
 */
void viewSchedules() {
  ScheduleNode *current = scheduleHead;
  printf("Festival Lineup:\n");

  while (current != NULL) {
    printf("ID: %d | Band: %s | Date: %s\n", current->scheduleID, current->bandName, current->date);
    current = current->next;
  }

  if (scheduleHead == NULL) {
    printf("No schedules available.\n");
  }
}

/**
 * @brief Deletes a schedule by its ID.
 * @param scheduleID The ID of the schedule to delete.
 * @return 1 if deletion is successful, 0 otherwise.
 */
int deleteSchedule(int scheduleID) {
  ScheduleNode *current = scheduleHead;

  while (current != NULL) {
    if (current->scheduleID == scheduleID) {
      if (current->prev) {
        current->prev->next = current->next;
      } else {
        scheduleHead = current->next; // Deleting the head node
      }

      if (current->next) {
        current->next->prev = current->prev;
      }

      free(current);
      printf("Schedule with ID %d deleted.\n", scheduleID);
      return 1;
    }

    current = current->next;
  }

  printf("Schedule ID %d not found.\n", scheduleID);
  return 0;
}

/**
 * @brief Loads schedules from a binary file.
 */
void loadScheduleDatabase() {
  FILE *file;
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
      createSchedule(scheduleID, bandName, date);
    }

    fclose(file);
  } else {
    printf("Error: Could not open file for reading.\n");
  }
}

/**
 * @brief Creates a new schedule entry.
 * @param scheduleID The schedule ID.
 * @param bandName The band name.
 * @param date The scheduled date.
 */
void createSchedule(int scheduleID, const char *bandName, const char *date) {
  ScheduleNode *newNode = (ScheduleNode *)malloc(sizeof(ScheduleNode));
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

/**
 * @brief Saves the schedule database to a binary file.
 */
void saveScheduleDatabase() {
  FILE *file;
  fopen_s(&file, "scheduleDatabase.bin", "wb");

  if (file) {
    ScheduleNode *current = scheduleHead;
    int count = 0;

    // Count nodes
    while (current != NULL) {
      count++;
      current = current->next;
    }

    // Write node count
    fwrite(&count, sizeof(int), 1, file);
    // Write schedule data
    current = scheduleHead;

    while (current != NULL) {
      fwrite(&(current->scheduleID), sizeof(int), 1, file);
      fwrite(current->bandName, sizeof(current->bandName), 1, file);
      fwrite(current->date, sizeof(current->date), 1, file);
      current = current->next;
    }

    fclose(file);
  } else {
    printf("Error: Could not open file for writing.\n");
  }
}

// Ticket Sales Tracking Functions

/**
 * @brief Creates a new B+ tree node.
 * @param isLeaf Indicates if the node is a leaf node.
 * @return Pointer to the newly created B+ tree node.
 */
BPlusTreeNode *createNode(bool isLeaf) {
  BPlusTreeNode *newNode = (BPlusTreeNode *)malloc(sizeof(BPlusTreeNode));
  newNode->isLeaf = isLeaf;
  newNode->numKeys = 0;
  newNode->next = NULL;

  for (int i = 0; i <= MAX_KEYS; i++) {
    newNode->children[i] = NULL;
  }

  return newNode;
}

/**
 * @brief Searches the B+ tree for a specific key.
 * @param key The key to search for.
 * @return Pointer to the ticket sale if found, NULL otherwise.
 */
TicketSale *searchBPlusTree(int key) {
  BPlusTreeNode *current = root;

  while (current != NULL) {
    int i = 0;

    while (i < current->numKeys && key > current->keys[i]) {
      i++;
    }

    if (i < current->numKeys && key == current->keys[i]) {
      return current->sales[i];
    }

    if (current->isLeaf) {
      return NULL;
    }

    current = current->children[i];
  }

  return NULL;
}

/**
 * @brief Inserts a new key and ticket sale into the B+ tree.
 * @param key The key to insert.
 * @param sale The associated ticket sale data.
 */
void insertBPlusNode(int key, TicketSale *sale) {
  if (root == NULL) {
    root = createNode(true);
    root->keys[0] = key;
    root->sales[0] = sale;
    root->numKeys = 1;
    return;
  }

  BPlusTreeNode *current = root;
  BPlusTreeNode *parent = NULL;

  while (!current->isLeaf) {
    parent = current;
    int i = 0;

    while (i < current->numKeys && key > current->keys[i]) {
      i++;
    }

    current = current->children[i];
  }

  if (current->numKeys < MAX_KEYS) {
    int i = current->numKeys - 1;

    while (i >= 0 && current->keys[i] > key) {
      current->keys[i + 1] = current->keys[i];
      current->sales[i + 1] = current->sales[i];
      i--;
    }

    current->keys[i + 1] = key;
    current->sales[i + 1] = sale;
    current->numKeys++;
  }
}

/**
 * @brief Displays the B+ tree contents.
 * @param node The root node of the B+ tree.
 */
void displayBPlusTree(BPlusTreeNode *node) {
  if (node == NULL) return;

  for (int i = 0; i < node->numKeys; i++) {
    printf("%d ", node->keys[i]);
  }

  printf("\n");

  if (!node->isLeaf) {
    for (int i = 0; i <= node->numKeys; i++) {
      displayBPlusTree(node->children[i]);
    }
  }
}

/**
 * @brief Initializes the B+ tree.
 */
void initializeBPlusTree() {
  root = NULL;
}

/**
 * @brief Loads sales data from the binary file and inserts it into the B+ tree.
 */
void loadSalesDatabase() {
  FILE *file = fopen("salesDatabase.bin", "rb");

  if (file == NULL) {
    printf("Failed to open salesDatabase.bin for reading.\n");
    return;
  }

  int sampleCount;
  fread(&sampleCount, sizeof(int), 1, file);
  TicketSale *sales = (TicketSale *)malloc(sampleCount * sizeof(TicketSale));
  fread(sales, sizeof(TicketSale), sampleCount, file);

  for (int i = 0; i < sampleCount; i++) {
    insertBPlusNode(sales[i].saleID, &sales[i]);
  }

  fclose(file);
  printf("Sales data loaded from salesDatabase.bin successfully.\n");
}

/**
 * @brief Displays all ticket sales data in the B+ tree.
 */
void viewSalesData() {
  printf("Ticket Sales Data:\n");
  BPlusTreeNode *current = root;

  if (current == NULL) {
    printf("No sales data available.\n");
    return;
  }

  // Move to the leftmost leaf
  while (!current->isLeaf) {
    current = current->children[0];
  }

  // Print all leaf nodes
  while (current != NULL) {
    for (int i = 0; i < current->numKeys; i++) {
      TicketSale *sale = current->sales[i];
      printf("Sale ID: %d, Type: %s, Amount: %.2f, Date: %s\n",
             sale->saleID, sale->ticketType, sale->amount, sale->date);
    }

    current = current->next;
  }
}

/**
 * @brief Saves a sample sales dataset to the binary file.
 */
void saveSampleSalesData() {
  FILE *file = fopen("salesDatabase.bin", "wb");

  if (file == NULL) {
    printf("Failed to open file for writing.\n");
    return;
  }

  TicketSale sampleSales[] = {
    {1, "Normal", 50.0, "2024-11-01"},
    {2, "Student", 30.0, "2024-11-02"},
    {3, "Normal", 45.0, "2024-11-03"},
    {4, "Student", 25.0, "2024-11-04"},
    {5, "Normal", 60.0, "2024-11-05"}
  };
  int sampleCount = sizeof(sampleSales) / sizeof(sampleSales[0]);
  fwrite(&sampleCount, sizeof(int), 1, file);
  fwrite(sampleSales, sizeof(TicketSale), sampleCount, file);
  fclose(file);
  printf("Sample sales data saved to salesDatabase.bin successfully.\n");
}

/**
 * @brief Generates a sales report summarizing ticket sales data.
 */
void generateSalesReport() {
  double totalAmount = 0.0;
  int normalCount = 0, studentCount = 0;
  BPlusTreeNode *current = root;

  while (current && !current->isLeaf) {
    current = current->children[0];
  }

  while (current) {
    for (int i = 0; i < current->numKeys; i++) {
      totalAmount += current->sales[i]->amount;

      if (strcmp(current->sales[i]->ticketType, "Normal") == 0) {
        normalCount++;
      } else if (strcmp(current->sales[i]->ticketType, "Student") == 0) {
        studentCount++;
      }
    }

    current = current->next;
  }

  printf("Sales Report:\n");
  printf("Total Sales Amount: %.2f\n", totalAmount);
  printf("Total 'Normal' Tickets Sold: %d\n", normalCount);
  printf("Total 'Student' Tickets Sold: %d\n", studentCount);
  printf("Total Sales Count: %d\n", salesCount);
}

// Vendor Management Functions

/**
 * @brief Adds a new vendor to the vendor list.
 * @param id The ID of the vendor.
 * @param name The name of the vendor.
 * @param serviceType The type of service provided by the vendor.
 */
void addVendor(int id, const char *name, const char *serviceType) {
  Vendor *newVendor = (Vendor *)malloc(sizeof(Vendor));
  newVendor->id = id;
  strcpy(newVendor->name, name);
  strcpy(newVendor->serviceType, serviceType);
  newVendor->next = vendorListHead;
  vendorListHead = newVendor;
}

/**
 * @brief Adds a new sponsor to the sponsor list.
 * @param id The ID of the sponsor.
 * @param name The name of the sponsor.
 * @param contributionAmount The amount contributed by the sponsor.
 */
void addSponsor(int id, const char *name, double contributionAmount) {
  Sponsor *newSponsor = (Sponsor *)malloc(sizeof(Sponsor));
  newSponsor->id = id;
  strcpy(newSponsor->name, name);
  newSponsor->contributionAmount = contributionAmount;
  newSponsor->next = sponsorListHead;
  sponsorListHead = newSponsor;
}

/**
 * @brief Saves the vendor database to a binary file.
 */
void saveVendorDatabase() {
  FILE *file;
  fopen_s(&file, "vendorDatabase.bin", "wb");
  Vendor *current = vendorListHead;

  while (current != NULL) {
    fwrite(current, sizeof(Vendor), 1, file);
    current = current->next;
  }

  fclose(file);
}

/**
 * @brief Saves the sponsor database to a binary file.
 */
void saveSponsorDatabase() {
  FILE *file;
  fopen_s(&file, "sponsorDatabase.bin", "wb");
  Sponsor *current = sponsorListHead;

  while (current != NULL) {
    fwrite(current, sizeof(Sponsor), 1, file);
    current = current->next;
  }

  fclose(file);
}

/**
 * @brief Loads the vendor database from a binary file and adds vendors to the list.
 */
void loadVendorDatabase() {
  FILE *file;
  fopen_s(&file, "vendorDatabase.bin", "rb");

  if (file) {
    Vendor temp;

    while (fread(&temp, sizeof(Vendor), 1, file)) {
      addVendor(temp.id, temp.name, temp.serviceType);
    }

    fclose(file);
  }
}

/**
 * @brief Loads the sponsor database from a binary file and adds sponsors to the list.
 */
void loadSponsorDatabase() {
  FILE *file;
  fopen_s(&file, "sponsorDatabase.bin", "rb");

  if (file) {
    Sponsor temp;

    while (fread(&temp, sizeof(Sponsor), 1, file)) {
      addSponsor(temp.id, temp.name, temp.contributionAmount);
    }

    fclose(file);
  }
}

/**
 * @brief Displays a menu for adding a new vendor and saves the vendor data.
 */
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

/**
 * @brief Displays a menu for adding a new sponsor and saves the sponsor data.
 */
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

/**
 * @brief Loads and displays the list of all vendors.
 */
void manageVendors() {
  loadVendorDatabase();  // Load the latest data
  Vendor *current = vendorListHead;
  printf("Vendors List:\n");

  while (current != NULL) {
    printf("ID: %d | Name: %s | Service: %s\n", current->id, current->name, current->serviceType);
    current = current->next;
  }
}

/**
 * @brief Loads and displays the list of all sponsors.
 */
void trackSponsors() {
  loadSponsorDatabase();  // Load the latest data
  Sponsor *current = sponsorListHead;
  printf("Sponsors List:\n");

  while (current != NULL) {
    printf("ID: %d | Name: %s | Contribution: %.2f\n", current->id, current->name, current->contributionAmount);
    current = current->next;
  }
}