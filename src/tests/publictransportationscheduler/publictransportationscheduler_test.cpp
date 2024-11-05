#include "gtest/gtest.h"
#include "publictransportationscheduler.h"

// Test class for PublicTransportationScheduler
class PublicTransportationSchedulerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Preparation operations before each test
    }

    void TearDown() override {
        // Cleanup operations after each test
    }
};

// Tests for user registration and login functions
/**
 * @brief Tests if user registration works and verifies login with registered credentials.
 */
TEST_F(PublicTransportationSchedulerTest, TestRegisterUser) {
    registerUser("testuser", "password");
    EXPECT_EQ(login("testuser", "password"), 1);  // Registration should be successful
}

/**
 * @brief Tests login with an invalid username.
 */
TEST_F(PublicTransportationSchedulerTest, TestLoginInvalidUser) {
    EXPECT_EQ(login("invaliduser", "password"), 0);  // Invalid username should fail
}

// Tests for ticket sales functions
/**
 * @brief Tests loading and viewing ticket sales data.
 */
TEST_F(PublicTransportationSchedulerTest, TestViewSalesData) {
    loadSalesDatabase();
    viewSalesData();
    EXPECT_GE(salesCount, 0);  // salesCount should be zero or more
}

/**
 * @brief Tests generating a sales report and verifies the total sales amount.
 */
TEST_F(PublicTransportationSchedulerTest, TestGenerateSalesReport) {
    generateSalesReport();
    double totalAmount = 0;
    for (int i = 0; i < salesCount; i++) {
        totalAmount += salesDatabase[i].amount;
    }
    EXPECT_GE(totalAmount, 0);  // Total sales amount should be zero or more
}

// Tests for vendor management functions
/**
 * @brief Tests loading and managing vendor data.
 */
TEST_F(PublicTransportationSchedulerTest, TestManageVendors) {
    loadVendorDatabase();
    manageVendors();
    EXPECT_GE(vendorCount, 0);  // vendorCount should be zero or more
}

// Tests for sponsor tracking functions
/**
 * @brief Tests loading and tracking sponsor data.
 */
TEST_F(PublicTransportationSchedulerTest, TestTrackSponsors) {
    loadSponsorDatabase();
    trackSponsors();
    EXPECT_GE(sponsorCount, 0);  // sponsorCount should be zero or more
}

// Tests for band and artist management functions
/**
 * @brief Tests adding a new band.
 */
TEST_F(PublicTransportationSchedulerTest, TestAddBand) {
    addBand("Test Band");
    ASSERT_EQ(bandDatabase[0].name, std::string("Test Band"));
}

/**
 * @brief Tests editing an existing band's name.
 */
TEST_F(PublicTransportationSchedulerTest, TestEditBand) {
    addBand("Old Band Name");
    editBand("Old Band Name", "New Band Name");
    ASSERT_EQ(bandDatabase[0].name, std::string("New Band Name"));
}

/**
 * @brief Tests viewing the list of bands.
 */
TEST_F(PublicTransportationSchedulerTest, TestViewBands) {
    addBand("View Band");
    viewBands();
    EXPECT_GE(bandCount, 1);  // bandCount should be one or more after adding a band
}

// Tests for schedule management functions
/**
 * @brief Tests creating a new schedule entry.
 */
TEST_F(PublicTransportationSchedulerTest, TestCreateSchedule) {
    createSchedule(1, "Band B", "2024-12-02");
    ASSERT_EQ(scheduleDatabase[0].bandName, std::string("Band B"));
    ASSERT_EQ(scheduleDatabase[0].date, std::string("2024-12-02"));
}

/**
 * @brief Tests editing an existing schedule entry.
 */
TEST_F(PublicTransportationSchedulerTest, TestEditSchedule) {
    createSchedule(1, "Band A", "2024-12-01");
    editSchedule(1, "Band B", "2024-12-02");
    ASSERT_EQ(scheduleDatabase[0].bandName, std::string("Band B"));
    ASSERT_EQ(scheduleDatabase[0].date, std::string("2024-12-02"));
}

/**
 * @brief Tests viewing the list of scheduled performances.
 */
TEST_F(PublicTransportationSchedulerTest, TestViewSchedules) {
    createSchedule(1, "View Band", "2024-12-01");
    viewSchedules();
    EXPECT_GE(scheduleCount, 1);  // scheduleCount should be one or more after adding a schedule
}

// Tests for double linked list functions
/**
 * @brief Tests inserting a node into a double linked list.
 */
TEST_F(PublicTransportationSchedulerTest, TestInsertDoubleNode) {
    DoubleNode* head = NULL;
    insertDoubleNode(&head, 5);
    ASSERT_EQ(head->data, 5);  // Verify that the inserted node's data is correct
}

/**
 * @brief Tests saving and loading a double linked list to/from a file.
 */
TEST_F(PublicTransportationSchedulerTest, TestSaveAndLoadDoubleLinkedList) {
    DoubleNode* head = NULL;
    insertDoubleNode(&head, 5);
    saveDoubleLinkedListToFile(head, "doublelist.bin");

    DoubleNode* loadedHead = NULL;
    loadDoubleLinkedListFromFile(&loadedHead, "doublelist.bin");
    ASSERT_EQ(loadedHead->data, 5);  // Verify that loaded data matches saved data
}

// Tests for XOR linked list functions
/**
 * @brief Tests inserting a node into an XOR linked list.
 */
TEST_F(PublicTransportationSchedulerTest, TestInsertXORNode) {
    XORNode* head = NULL;
    insertXORNode(&head, 5);
    ASSERT_EQ(head->data, 5);  // Verify that the inserted node's data is correct
}

/**
 * @brief Tests saving and loading an XOR linked list to/from a file.
 */
TEST_F(PublicTransportationSchedulerTest, TestSaveAndLoadXORLinkedList) {
    XORNode* head = NULL;
    insertXORNode(&head, 5);
    saveXORLinkedListToFile(head, "xorlist.bin");

    XORNode* loadedHead = NULL;
    loadXORLinkedListFromFile(&loadedHead, "xorlist.bin");
    ASSERT_EQ(loadedHead->data, 5);  // Verify that loaded data matches saved data
}

// Tests for sparse matrix functions
/**
 * @brief Tests inserting a node into a sparse matrix.
 */
TEST_F(PublicTransportationSchedulerTest, TestInsertSparseNode) {
    SparseMatrixNode* head = NULL;
    insertSparseNode(&head, 0, 0, 5);
    ASSERT_EQ(head->value, 5);  // Verify that the inserted node's value is correct
}

/**
 * @brief Tests saving and loading a sparse matrix to/from a file.
 */
TEST_F(PublicTransportationSchedulerTest, TestSaveAndLoadSparseMatrix) {
    SparseMatrixNode* head = NULL;
    insertSparseNode(&head, 0, 0, 5);
    saveSparseMatrixToFile(head, "sparsematrix.bin");

    SparseMatrixNode* loadedHead = NULL;
    loadSparseMatrixFromFile(&loadedHead, "sparsematrix.bin");
    ASSERT_EQ(loadedHead->value, 5);  // Verify that loaded data matches saved data
}
