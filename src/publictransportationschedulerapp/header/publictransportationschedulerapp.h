#ifndef PUBLICTRANSPORTATIONSCHEDULER_H
#define PUBLICTRANSPORTATIONSCHEDULER_H

#include <stdint.h>
#include <stdbool.h>  // B+ ağacı için gerekli olabilir

// User structure
/**
 * @brief Structure to hold user data, including username and password.
 */
    typedef struct {
    char username[50]; / < User's username */
        char password[50]; / < User's password */
} User;

// Band structure
/**
 * @brief Structure to hold band information.
 */
typedef struct {
    char name[50]; / < Name of the band * /
} Band;

// Schedule structure to manage event scheduling
/**
 * @brief Structure for managing event schedules.
 */
typedef struct ScheduleNode {
    int scheduleID; / < Unique ID for the schedule* /
        char bandName[50]; / < Name of the band performing * /
        char date[20]; / < Date of the schedule * /
        struct ScheduleNode* next; / < Pointer to the next schedule in the list * /
        struct ScheduleNode* prev; / < Pointer to the previous schedule in the list * /
} ScheduleNode;

ScheduleNode* scheduleHead = NULL; / < Head pointer for the schedule linked list* /

    // Ticket Sale structure
    /**
     * @brief Structure to manage ticket sale information.
     */
    typedef struct {
    int saleID; / < Unique sale ID * /
        char ticketType[20]; / < Type of ticket(e.g., Normal, Student) * /
        float amount; / < Sale amount * /
        char date[20]; / < Date of the sale * /
} TicketSale;

// Vendor structure to manage vendors
/**
 * @brief Structure to hold vendor information.
 */
typedef struct Vendor {
    int id; / < Vendor ID * /
        char name[50]; / < Vendor name * /
        char serviceType[50]; / < Type of service provided by the vendor * /
        struct Vendor* next; / < Pointer to the next vendor in the list * /
} Vendor;

// Sponsor structure to manage sponsors
/**
 * @brief Structure to hold sponsor information.
 */
typedef struct Sponsor {
    int id; / < Sponsor ID * /
        char name[50]; / < Sponsor name * /
        double contributionAmount; / < Sponsor's contribution amount */
        struct Sponsor* next; / < Pointer to the next sponsor in the list * /
} Sponsor;

// Global vendor and sponsor lists
Vendor* vendorListHead = NULL; / < Head pointer for the vendor linked list* /
    Sponsor * sponsorListHead = NULL; / < Head pointer for the sponsor linked list* /

    // Double Linked List Node for routes
    /**
     * @brief Node structure for a double linked list to manage routes.
     */
    typedef struct DoubleNode {
    int data; / < Route ID * /
        char routeName[50]; / < Name of the route * /
        char startPoint[50]; / < Starting point of the route * /
        char endPoint[50]; / < Ending point of the route * /
        struct DoubleNode* next; / < Pointer to the next node * /
        struct DoubleNode* prev; / < Pointer to the previous node * /
} DoubleNode;

// XOR Linked List Node structure
/**
 * @brief Node structure for an XOR linked list.
 */
typedef struct XORNode {
    int data; / < Data value for the XOR node* /
        struct XORNode* npx; / < XOR of next and previous node pointers * /
} XORNode;

// Sparse Matrix Node structure
/**
 * @brief Node structure for a sparse matrix representation.
 */
typedef struct SparseMatrixNode {
    int row; / < Row index in the sparse matrix * /
        int col; / < Column index in the sparse matrix * /
        int value; / < Value at the specified position * /
        struct SparseMatrixNode* next; / < Pointer to the next sparse matrix node * /
} SparseMatrixNode;

// Stack and Queue Node structure
/**
 * @brief Node structure for stack and queue operations.
 */
typedef struct Node {
    int data; / < Data value for stack or queue * /
        struct Node* next; / < Pointer to the next node * /
} Node;

// B+ Tree Node structure
#define MAX_KEYS 4  /< Maximum keys per B+ tree node */

/**
 * @brief B+ Tree node structure for managing sales data.
 */
typedef struct BPlusTreeNode {
    int keys[MAX_KEYS]; / < Array of keys * /
        TicketSale * sales[MAX_KEYS]; / < Array of sales associated with keys * /
        struct BPlusTreeNode* children[MAX_KEYS + 1]; / < Array of child pointers * /
        int numKeys; / < Number of keys currently in the node * /
        bool isLeaf; / < Flag indicating if the node is a leaf* /
        struct BPlusTreeNode* next; / < Pointer to the next leaf node * /
} BPlusTreeNode;

BPlusTreeNode* root = NULL; / < Root pointer for the B + tree * /

    // Function prototypes with documentation for testing

    /**
     * @brief Initializes the hash table.
     */
    void initializeHashTable();

/**
 * @brief Computes the hash index for a given key.
 * @param key The key to hash.
 * @return Hash index as an integer.
 */
int hashFunction(const char* key);

/**
 * @brief Adds a user to the hash table.
 * @param username User's username.
 * @param password User's password.
 */
void addUserToHashTable(const char* username, const char* password);

/**
 * @brief Verifies if the user exists in the hash table.
 * @param username User's username.
 * @param password User's password.
 * @return 1 if user exists, 0 otherwise.
 */
int verifyUserInHashTable(const char* username, const char* password);

// Double Linked List Functions
/**
 * @brief Inserts a node with data into the double linked list.
 * @param head Pointer to the head of the list.
 * @param data Data to insert.
 */
void insertDoubleNode(DoubleNode * *head, int data);

/**
 * @brief Prints all nodes in the double linked list.
 * @param head Pointer to the head of the list.
 */
void printDoubleList(DoubleNode * head);

/**
 * @brief Finds a node with the given data in the double linked list.
 * @param head Pointer to the head of the list.
 * @param data Data to search for.
 * @return Pointer to the node if found, NULL otherwise.
 */
DoubleNode* findDoubleNode(DoubleNode * head, int data);

/**
 * @brief Deletes a node with the given data from the double linked list.
 * @param head Pointer to the head of the list.
 * @param data Data of the node to delete.
 * @return 1 if deletion was successful, 0 otherwise.
 */
int deleteDoubleNode(DoubleNode * *head, int data);

// XOR Linked List Functions
/**
 * @brief XORs two pointers.
 * @param a First pointer.
 * @param b Second pointer.
 * @return XORed pointer.
 */
XORNode* XOR(XORNode * a, XORNode * b);

/**
 * @brief Inserts a node into the XOR linked list.
 * @param head Pointer to the head of the list.
 * @param data Data to insert.
 */
void insertXORNode(XORNode * *head, int data);

// Sparse Matrix Functions
/**
 * @brief Inserts a node into the sparse matrix.
 * @param head Pointer to the head of the sparse matrix.
 * @param row Row index.
 * @param col Column index.
 * @param value Value at the specified index.
 */
void insertSparseNode(SparseMatrixNode * *head, int row, int col, int value);

// Stack and Queue Functions
/**
 * @brief Pushes data onto the stack.
 * @param data Data to push.
 */
void push(int data);

/**
 * @brief Pops data from the stack.
 * @return Popped data.
 */
int pop();

/**
 * @brief Enqueues data into the queue.
 * @param data Data to enqueue.
 */
void enqueue(int data);

/**
 * @brief Dequeues data from the queue.
 * @return Dequeued data.
 */
int dequeue();

// Priority Queue (Heap) Functions
/**
 * @brief Inserts data into the heap.
 * @param data Data to insert.
 */
void insertHeap(int data);

/**
 * @brief Extracts the minimum data from the heap.
 * @return Extracted minimum data.
 */
int extractMin();

// BFS and DFS Functions
/**
 * @brief Performs a breadth-first search starting from a node.
 * @param startNode Starting node for BFS.
 */
void bfs(int startNode);

/**
 * @brief Performs a depth-first search starting from a node.
 * @param startNode Starting node for DFS.
 */
void dfs(int startNode);

// Huffman Coding Functions
/**
 * @brief Compresses data using Huffman coding.
 * @param data Data to compress.
 */
void compressDataHuffman(const char* data);

/**
 * @brief Decompresses data compressed with Huffman coding.
 */
void decompressDataHuffman();

// KMP Algorithm Functions
/**
 * @brief Searches for a pattern in a text using the KMP algorithm.
 * @param pattern Pattern to search.
 * @param text Text to search within.
 */
void KMPSearch(const char* pattern, const char* text);

// User Database Functions
/**
 * @brief Loads the user database from a file.
 */
void loadUserDatabase();

/**
 * @brief Saves the user database to a file.
 */
void saveUserDatabase();

/**
 * @brief Logs a user in by verifying credentials.
 * @param username User's username.
 * @param password User's password.
 * @return 1 if login is successful, 0 otherwise.
 */
int login(const char* username, const char* password);

/**
 * @brief Registers a new user.
 * @param username User's username.
 * @param password User's password.
 */
void registerUser(const char* username, const char* password);

// Band Management Functions
/**
 * @brief Loads the band database from a file.
 */
void loadBandDatabase();

/**
 * @brief Saves the band database to a file.
 */
void saveBandDatabase();

/**
 * @brief Adds a band to the database.
 * @param name Name of the band.
 */
void addBand(const char* name);

/**
 * @brief Edits an existing band's name.
 * @param oldName Current name of the band.
 * @param newName New name for the band.
 */
void editBand(const char* oldName, const char* newName);

/**
 * @brief Displays all bands in the database.
 */
void viewBands();

// Schedule Management Functions
/**
 * @brief Loads the schedule database from a file.
 */
void loadScheduleDatabase();

/**
 * @brief Saves the schedule database to a file.
 */
void saveScheduleDatabase();

/**
 * @brief Creates a new schedule entry.
 * @param scheduleID ID of the schedule.
 * @param bandName Name of the performing band.
 * @param date Date of the schedule.
 */
void createSchedule(int scheduleID, const char* bandName, const char* date);

/**
 * @brief Displays all schedules in the database.
 */
void viewSchedules();

// B+ Tree Functions for Sales Management
/**
 * @brief Inserts a sale into the B+ tree.
 * @param key Sale ID.
 * @param sale Pointer to the sale data.
 */
void insertBPlusNode(int key, TicketSale * sale);

/**
 * @brief Displays the B+ tree structure.
 * @param node Pointer to the B+ tree node.
 */
void displayBPlusTree(BPlusTreeNode * node);

/**
 * @brief Searches for a sale in the B+ tree by ID.
 * @param key Sale ID to search for.
 * @return Pointer to the sale data, or NULL if not found.
 */
TicketSale* searchBPlusTree(int key);

/**
 * @brief Initializes the B+ tree structure.
 */
void initializeBPlusTree();

/**
 * @brief Loads the vendor database from a file.
 */
void loadVendorDatabase();

/**
 * @brief Saves the vendor database to a file.
 */
void saveVendorDatabase();

/**
 * @brief Adds a vendor through menu input.
 */
void addVendorMenu();

/**
 * @brief Loads the sponsor database from a file.
 */
void loadSponsorDatabase();

/**
 * @brief Saves the sponsor database to a file.
 */
void saveSponsorDatabase();

/**
 * @brief Tracks all sponsors in the list.
 */
void trackSponsors();

#endif // PUBLICTRANSPORTATIONSCHEDULER_H