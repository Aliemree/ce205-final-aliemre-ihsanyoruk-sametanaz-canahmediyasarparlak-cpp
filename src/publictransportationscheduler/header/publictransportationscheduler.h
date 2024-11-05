#ifndef PUBLICTRANSPORTATIONSCHEDULER_H
#define PUBLICTRANSPORTATIONSCHEDULER_H

#include <stdint.h>  // for uintptr_t

// User structure
/**
 * @brief Structure representing a user with a username and password.
 */
typedef struct {
    char username[50];
    char password[50];
} User;

extern User userDatabase[100];
extern int userCount;

/**
 * @brief Loads the user database from a file.
 */
void loadUserDatabase();

/**
 * @brief Saves the user database to a file.
 */
void saveUserDatabase();

/**
 * @brief Logs in a user by checking their username and password.
 * @param username The username to verify
 * @param password The password to verify
 * @return 1 if login is successful, 0 otherwise
 */
int login(const char* username, const char* password);

/**
 * @brief Registers a new user by adding them to the database.
 * @param username The username for the new user
 * @param password The password for the new user
 */
void registerUser(const char* username, const char* password);

/**
 * @brief Activates guest mode with limited access.
 */
void activateGuestMode();

// Band structure
/**
 * @brief Structure representing a band or artist.
 */
typedef struct {
    char name[50];
} Band;

extern Band bandDatabase[100];
extern int bandCount;

/**
 * @brief Loads the band database from a file.
 */
void loadBandDatabase();

/**
 * @brief Saves the band database to a file.
 */
void saveBandDatabase();

/**
 * @brief Adds a new band or artist to the database.
 * @param name The name of the band or artist to add
 */
void addBand(const char* name);

/**
 * @brief Edits an existing band's name.
 * @param oldName The current name of the band
 * @param newName The new name of the band
 */
void editBand(const char* oldName, const char* newName);

/**
 * @brief Displays the list of bands and artists.
 */
void viewBands();

// Schedule structure
/**
 * @brief Structure representing a performance schedule with a unique ID, band name, and date.
 */
typedef struct {
    int scheduleID;
    char bandName[50];
    char date[20];
} Schedule;

extern Schedule scheduleDatabase[100];
extern int scheduleCount;

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
 * @param scheduleID The unique ID of the schedule
 * @param bandName The name of the band performing
 * @param date The date of the performance
 */
void createSchedule(int scheduleID, const char* bandName, const char* date);

/**
 * @brief Edits an existing schedule entry.
 * @param scheduleID The ID of the schedule to edit
 * @param newBandName The new band name for the schedule
 * @param newDate The new date for the schedule
 */
void editSchedule(int scheduleID, const char* newBandName, const char* newDate);

/**
 * @brief Displays all scheduled performances.
 */
void viewSchedules();

// Ticket sale data structure
/**
 * @brief Structure representing a ticket sale with ID, type, amount, and date.
 */
typedef struct {
    int saleID;
    char ticketType[20];
    double amount;
    char date[20];
} TicketSale;

extern TicketSale salesDatabase[100];
extern int salesCount;

/**
 * @brief Loads the ticket sales database from a file.
 */
void loadSalesDatabase();

/**
 * @brief Saves the ticket sales database to a file.
 */
void saveSalesDatabase();

/**
 * @brief Displays all ticket sales data.
 */
void viewSalesData();

/**
 * @brief Generates a sales report summarizing total ticket sales.
 */
void generateSalesReport();

// Vendor structure
/**
 * @brief Structure representing a vendor with ID, name, and service type.
 */
typedef struct {
    int vendorID;
    char name[50];
    char serviceType[50];
} Vendor;

extern Vendor vendorDatabase[100];
extern int vendorCount;

/**
 * @brief Loads the vendor database from a file.
 */
void loadVendorDatabase();

/**
 * @brief Saves the vendor database to a file.
 */
void saveVendorDatabase();

/**
 * @brief Manages the list of vendors.
 */
void manageVendors();

// Sponsor structure
/**
 * @brief Structure representing a sponsor with ID, name, and contribution amount.
 */
typedef struct {
    int sponsorID;
    char name[50];
    double contributionAmount;
} Sponsor;

extern Sponsor sponsorDatabase[100];
extern int sponsorCount;

/**
 * @brief Loads the sponsor database from a file.
 */
void loadSponsorDatabase();

/**
 * @brief Saves the sponsor database to a file.
 */
void saveSponsorDatabase();

/**
 * @brief Tracks and displays sponsor contributions.
 */
void trackSponsors();

// Fare Calculation and Delay Notification Functions
/**
 * @brief Calculates the fare based on the route and ticket type.
 * @param route The route for the fare calculation
 * @param ticketType The type of ticket (e.g., "Student", "Regular")
 */
void calculateFare(const char* route, const char* ticketType);

/**
 * @brief Alerts for any delays in the schedule.
 */
void alertForDelays();

// Data Compression and Decompression Functions (Example functions)
/**
 * @brief Compresses data and saves it (example function).
 * @param data The data to compress and save
 */
void compressAndSaveData(const char* data);

/**
 * @brief Decompresses data (example function).
 * @return A string of decompressed data
 */
char* decompressData();

// Double Linked List Functions
/**
 * @brief Structure representing a node in a double linked list.
 */
typedef struct DoubleNode {
    int data;
    struct DoubleNode* next;
    struct DoubleNode* prev;
} DoubleNode;

/**
 * @brief Inserts a new node with data at the beginning of a double linked list.
 * @param head The pointer to the head of the list
 * @param data The data to insert in the new node
 */
void insertDoubleNode(DoubleNode** head, int data);

/**
 * @brief Deletes a node with specific data from the double linked list.
 * @param head The pointer to the head of the list
 * @param data The data of the node to delete
 */
void deleteDoubleNode(DoubleNode** head, int data);

/**
 * @brief Prints all elements in the double linked list.
 * @param head The head of the list
 */
void printDoubleList(DoubleNode* head);

/**
 * @brief Saves a double linked list to a file.
 * @param head The head of the list
 * @param filename The file to save the list
 */
void saveDoubleLinkedListToFile(DoubleNode* head, const char* filename);

/**
 * @brief Loads a double linked list from a file.
 * @param head The pointer to the head of the list
 * @param filename The file to load the list from
 */
void loadDoubleLinkedListFromFile(DoubleNode** head, const char* filename);

// XOR Linked List Functions
/**
 * @brief Structure representing a node in an XOR linked list.
 */
typedef struct XORNode {
    int data;
    struct XORNode* npx;  // XOR of next and previous node
} XORNode;

/**
 * @brief XORs two pointers to get a combined pointer.
 * @param a The first pointer
 * @param b The second pointer
 * @return The XORed result
 */
XORNode* XOR(XORNode* a, XORNode* b);

/**
 * @brief Inserts a new node with data into an XOR linked list.
 * @param head The pointer to the head of the XOR linked list
 * @param data The data to insert in the new node
 */
void insertXORNode(XORNode** head, int data);

/**
 * @brief Prints all elements in the XOR linked list.
 * @param head The head of the XOR linked list
 */
void printXORList(XORNode* head);

/**
 * @brief Saves an XOR linked list to a file.
 * @param head The head of the XOR linked list
 * @param filename The file to save the list
 */
void saveXORLinkedListToFile(XORNode* head, const char* filename);

/**
 * @brief Loads an XOR linked list from a file.
 * @param head The pointer to the head of the XOR linked list
 * @param filename The file to load the list from
 */
void loadXORLinkedListFromFile(XORNode** head, const char* filename);

// Sparse Matrix Functions
/**
 * @brief Structure representing a node in a sparse matrix.
 */
typedef struct SparseMatrixNode {
    int row;
    int col;
    int value;
    struct SparseMatrixNode* next;
} SparseMatrixNode;

/**
 * @brief Inserts a new node with data into the sparse matrix.
 * @param head The pointer to the head of the sparse matrix
 * @param row The row index of the new node
 * @param col The column index of the new node
 * @param value The value to insert in the matrix node
 */
void insertSparseNode(SparseMatrixNode** head, int row, int col, int value);

/**
 * @brief Prints all elements in the sparse matrix.
 * @param head The head of the sparse matrix
 */
void printSparseMatrix(SparseMatrixNode* head);

/**
 * @brief Saves a sparse matrix to a file.
 * @param head The head of the sparse matrix
 * @param filename The file to save the matrix
 */
void saveSparseMatrixToFile(SparseMatrixNode* head, const char* filename);

/**
 * @brief Loads a sparse matrix from a file.
 * @param head The pointer to the head of the sparse matrix
 * @param filename The file to load the matrix from
 */
void loadSparseMatrixFromFile(SparseMatrixNode** head, const char* filename);

#endif // PUBLICTRANSPORTATIONSCHEDULER_H
