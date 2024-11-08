#include <gtest/gtest.h>
#include "publictransportationscheduler.h"
#include "../../publictransportationscheduler/src/publictransportationscheduler.cpp"

// Test class
class PublicTransportationSchedulerTest : public ::testing::Test {
protected:
    void SetUp() override {
        initializeHashTable();
        vendorListHead = NULL;
        sponsorListHead = NULL;
        scheduleHead = NULL;
        root = NULL;
        bandCount = 0;
        memset(bandDatabase, 0, sizeof(bandDatabase));
    }

    void TearDown() override {
        // Reset all global variables and data structures
        userCount = 0;
        bandCount = 0;
        scheduleHead = NULL;
        vendorListHead = NULL;
        sponsorListHead = NULL;
        routeListHead = NULL;
        root = NULL;
        remove("bandDatabase.bin");
    }
};

// User registration and login tests
TEST_F(PublicTransportationSchedulerTest, TestRegisterUser) {
    registerUser("uniqueuser", "password");
    EXPECT_EQ(login("uniqueuser", "password"), 1);  // Registration should be successful
}

TEST_F(PublicTransportationSchedulerTest, TestLoginInvalidUser) {
    EXPECT_EQ(login("invaliduser", "password"), 0);  // Invalid user login should fail
}

// Band management tests
TEST_F(PublicTransportationSchedulerTest, TestAddBand) {
    addBand("Test Band");
    EXPECT_STREQ(bandDatabase[0].name, "Test Band"); // Check band name
}

TEST_F(PublicTransportationSchedulerTest, TestEditBand) {
    addBand("Old Band Name");
    editBand("Old Band Name", "New Band Name");

    // Check if band name was updated
    EXPECT_STREQ(bandDatabase[0].name, "New Band Name");
}

// Schedule management tests
TEST_F(PublicTransportationSchedulerTest, TestCreateSchedule) {
    createSchedule(1, "Band B", "2024-12-02");
    EXPECT_STREQ(scheduleHead->bandName, "Band B"); // Check schedule band name
    EXPECT_STREQ(scheduleHead->date, "2024-12-02"); // Check schedule date
}

TEST_F(PublicTransportationSchedulerTest, TestEditSchedule) {
    createSchedule(1, "Band A", "2024-12-01");
    editSchedule(1, "Band B", "2024-12-02");
    EXPECT_STREQ(scheduleHead->bandName, "Band B"); // Updated band name
    EXPECT_STREQ(scheduleHead->date, "2024-12-02"); // Updated date
}

// Ticket sales tests
TEST_F(PublicTransportationSchedulerTest, TestViewSalesData) {
    loadSalesDatabase(); // Load sales data
    viewSalesData(); // View sales data
    EXPECT_GE(salesCount, 0);  // Sales count should be zero or more
}

TEST_F(PublicTransportationSchedulerTest, TestGenerateSalesReport) {
    generateSalesReport();
    double totalAmount = 0;

    for (int i = 0; i < salesCount; i++) {
        totalAmount += salesDatabase[i].amount;
    }

    EXPECT_GE(totalAmount, 0); // Total sales amount should be zero or more
}

// Vendor management tests
TEST_F(PublicTransportationSchedulerTest, TestManageVendors) {
    addVendor(1, "Vendor A", "Food");
    EXPECT_STREQ(vendorListHead->name, "Vendor A"); // Check vendor addition
}

// Sponsor tracking tests
TEST_F(PublicTransportationSchedulerTest, TestTrackSponsors) {
    addSponsor(1, "Sponsor A", 1000.0);
    EXPECT_STREQ(sponsorListHead->name, "Sponsor A"); // Check sponsor addition
}

// Doubly linked list tests
TEST_F(PublicTransportationSchedulerTest, TestInsertDoubleNode) {
    DoubleNode* head = NULL;
    insertDoubleNode(&head, 5);
    EXPECT_EQ(head->data, 5); // Check inserted node data
}

TEST_F(PublicTransportationSchedulerTest, TestDeleteDoubleNode) {
    DoubleNode* head = NULL;
    insertDoubleNode(&head, 5);
    insertDoubleNode(&head, 10);
    EXPECT_EQ(deleteDoubleNode(&head, 5), 1); // Node should be deleted
    EXPECT_EQ(head->data, 10); // Check remaining node data
}

// XOR linked list tests
TEST_F(PublicTransportationSchedulerTest, TestInsertXORNode) {
    XORNode* head = NULL;
    insertXORNode(&head, 5);
    EXPECT_EQ(head->data, 5); // Check inserted node data
}

// Sparse matrix tests
TEST_F(PublicTransportationSchedulerTest, TestInsertSparseNode) {
    SparseMatrixNode* head = NULL;
    insertSparseNode(&head, 0, 0, 5);
    EXPECT_EQ(head->value, 5); // Check inserted value
}

// General function tests
TEST_F(PublicTransportationSchedulerTest, TestHashTableFunctions) {
    addUserToHashTable("user1", "pass1");
    EXPECT_EQ(verifyUserInHashTable("user1", "pass1"), 1); // Check user verification
}

TEST_F(PublicTransportationSchedulerTest, TestViewBands) {
    addBand("View Band");
    EXPECT_GE(bandCount, 1); // Band count should be one or more
}

// B+ tree tests
TEST_F(PublicTransportationSchedulerTest, TestInsertBPlusNode) {
    TicketSale sale = { 1, "Normal", 50.0, "2024-11-01" };
    insertBPlusNode(sale.saleID, &sale);
    TicketSale* foundSale = searchBPlusTree(sale.saleID);
    EXPECT_NE(foundSale, nullptr); // Sale should be found
    EXPECT_EQ(foundSale->amount, 50.0); // Check amount
}

// Initialization tests
TEST_F(PublicTransportationSchedulerTest, TestInitializeBPlusTree) {
    initializeBPlusTree();
    EXPECT_EQ(root, nullptr); // Root node should be null initially
}

// Database tests
TEST_F(PublicTransportationSchedulerTest, TestLoadUserDatabase) {
    loadUserDatabase();
    EXPECT_GE(userCount, 0); // User count should be zero or more
}

TEST_F(PublicTransportationSchedulerTest, TestSaveUserDatabase) {
    registerUser("userToSave", "password");
    saveUserDatabase();
    EXPECT_EQ(login("userToSave", "password"), 1); // Verify saved user
}

TEST_F(PublicTransportationSchedulerTest, TestLoadBandDatabase) {
    loadBandDatabase();
    EXPECT_GE(bandCount, 0); // Band count should be zero or more
}

TEST_F(PublicTransportationSchedulerTest, TestSaveAndLoadBandDatabase) {
    // Add bands
    addBand("Band to Save 1");
    addBand("Band to Save 2");
    addBand("Band to Save 3");

    // Save database
    saveBandDatabase();

    // Reset band database and count, then reload
    bandCount = 0;
    memset(bandDatabase, 0, sizeof(bandDatabase));
    loadBandDatabase();

    // Check loaded data
    EXPECT_EQ(bandCount, 3); // 3 bands should be saved
    EXPECT_STREQ(bandDatabase[0].name, "Band to Save 1");
    EXPECT_STREQ(bandDatabase[1].name, "Band to Save 2");
    EXPECT_STREQ(bandDatabase[2].name, "Band to Save 3");
}

// Complete application flow test
TEST_F(PublicTransportationSchedulerTest, TestCompleteFlow) {
    registerUser("flowuser", "flowpassword");
    EXPECT_EQ(login("flowuser", "flowpassword"), 1);
    addRoute(2, "Flow Route", "Flow Start", "Flow End");
    EXPECT_EQ(findDoubleNode(routeListHead, 2)->data, 2); // Route should be added
}
