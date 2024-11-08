#include <gtest/gtest.h>
#include "publictransportationscheduler.h"
#include "../../publictransportationscheduler/src/publictransportationscheduler.cpp"

// Test class setup for main functionality
class PublicTransportationSchedulerTest : public ::testing::Test {
protected:
    // Setup method to initialize structures and data before each test
    void SetUp() override {
        initializeHashTable();
        vendorListHead = NULL;
        sponsorListHead = NULL;
        scheduleHead = NULL;
        routeListHead = NULL;
        root = NULL;
        userCount = 0;
        bandCount = 0;
        scheduleCount = 0;
        salesCount = 0;
        vendorCount = 0;
        sponsorCount = 0;
        memset(bandDatabase, 0, sizeof(bandDatabase));
    }

    // TearDown method to clean up after each test
    void TearDown() override {
        routeListHead = NULL;
        scheduleHead = NULL;
        vendorListHead = NULL;
        sponsorListHead = NULL;
        root = NULL;
    }
};

// Test user creation and hash table functions
TEST_F(PublicTransportationSchedulerTest, TestHashTableFunctions) {
    addUserToHashTable("testuser", "testpass");
    EXPECT_EQ(verifyUserInHashTable("testuser", "testpass"), 1);  // Should find user
    EXPECT_EQ(verifyUserInHashTable("nonexistent", "testpass"), 0);  // Should not find user
}

// Test adding and finding a route in double linked list
TEST_F(PublicTransportationSchedulerTest, TestAddAndFindRoute) {
    addRoute(1, "Route1", "Start1", "End1");
    DoubleNode* node = findDoubleNode(routeListHead, 1);
    ASSERT_NE(node, nullptr);  // Route should be found
    EXPECT_EQ(node->data, 1);
    EXPECT_STREQ(node->routeName, "Route1");
}

// Test XOR linked list insertion
TEST_F(PublicTransportationSchedulerTest, TestInsertXORNode) {
    XORNode* head = NULL;
    insertXORNode(&head, 1);
    insertXORNode(&head, 2);
    EXPECT_EQ(head->data, 2);  // Newest node should be head
    EXPECT_EQ(head->npx->data, 1);  // Next node should have data 1
}

// Test inserting a node in sparse matrix
TEST_F(PublicTransportationSchedulerTest, TestInsertSparseNode) {
    SparseMatrixNode* head = NULL;
    insertSparseNode(&head, 0, 1, 5);
    EXPECT_EQ(head->row, 0);
    EXPECT_EQ(head->col, 1);
    EXPECT_EQ(head->value, 5);
}

// Test stack operations
TEST_F(PublicTransportationSchedulerTest, TestStackOperations) {
    push(10);
    push(20);
    EXPECT_EQ(pop(), 20);  // Last in, first out
    EXPECT_EQ(pop(), 10);
    EXPECT_EQ(pop(), -1);  // Stack should be empty
}

// Test queue operations
TEST_F(PublicTransportationSchedulerTest, TestQueueOperations) {
    enqueue(30);
    enqueue(40);
    EXPECT_EQ(dequeue(), 30);  // First in, first out
    EXPECT_EQ(dequeue(), 40);
    EXPECT_EQ(dequeue(), -1);  // Queue should be empty
}

// Test heap operations
TEST_F(PublicTransportationSchedulerTest, TestHeapOperations) {
    insertHeap(30);
    insertHeap(10);
    insertHeap(20);
    EXPECT_EQ(extractMin(), 10);  // Minimum element
    EXPECT_EQ(extractMin(), 20);
    EXPECT_EQ(extractMin(), 30);
}

// Test band management functions
TEST_F(PublicTransportationSchedulerTest, TestBandManagement) {
    addBand("Test Band");
    EXPECT_EQ(bandCount, 1);  // Band count should update
    EXPECT_STREQ(bandDatabase[0].name, "Test Band");
    editBand("Test Band", "Updated Band");
    EXPECT_STREQ(bandDatabase[0].name, "Updated Band");  // Check edit
}

// Test schedule management functions
TEST_F(PublicTransportationSchedulerTest, TestScheduleManagement) {
    createSchedule(1, "Band A", "2024-11-10");
    EXPECT_EQ(scheduleHead->scheduleID, 1);
    EXPECT_STREQ(scheduleHead->bandName, "Band A");
    EXPECT_STREQ(scheduleHead->date, "2024-11-10");

    editSchedule(1, "Band B", "2024-11-15");
    EXPECT_STREQ(scheduleHead->bandName, "Band B");
    EXPECT_STREQ(scheduleHead->date, "2024-11-15");

    EXPECT_EQ(deleteSchedule(1), 1);  // Schedule deletion
}

// Test vendor and sponsor management
TEST_F(PublicTransportationSchedulerTest, TestVendorAndSponsorManagement) {
    addVendor(1, "Vendor A", "Food");
    EXPECT_EQ(vendorListHead->id, 1);
    EXPECT_STREQ(vendorListHead->name, "Vendor A");

    addSponsor(1, "Sponsor A", 1000.0);
    EXPECT_EQ(sponsorListHead->id, 1);
    EXPECT_DOUBLE_EQ(sponsorListHead->contributionAmount, 1000.0);
}

// B+ tree operations for ticket sales
TEST_F(PublicTransportationSchedulerTest, TestBPlusTreeOperations) {
    TicketSale sale1 = { 1, "Normal", 50.0, "2024-12-01" };
    TicketSale sale2 = { 2, "Student", 30.0, "2024-12-02" };
    insertBPlusNode(sale1.saleID, &sale1);
    insertBPlusNode(sale2.saleID, &sale2);

    TicketSale* foundSale = searchBPlusTree(1);
    ASSERT_NE(foundSale, nullptr);
    EXPECT_EQ(foundSale->saleID, 1);
    EXPECT_FLOAT_EQ(foundSale->amount, 50.0);
}

// Generate sales report test
TEST_F(PublicTransportationSchedulerTest, TestGenerateSalesReport) {
    TicketSale sale1 = { 1, "Normal", 50.0, "2024-12-01" };
    TicketSale sale2 = { 2, "Student", 30.0, "2024-12-02" };
    insertBPlusNode(sale1.saleID, &sale1);
    insertBPlusNode(sale2.saleID, &sale2);

    testing::internal::CaptureStdout();
    generateSalesReport();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Total Sales Amount") != std::string::npos);
}

// Additional tests for struct creation and linking

class PublicTransportationSchedulerStructsTest : public ::testing::Test {
protected:
    void SetUp() override {
        scheduleHead = NULL;
        vendorListHead = NULL;
        sponsorListHead = NULL;
        root = NULL;
    }

    void TearDown() override {
        scheduleHead = NULL;
        vendorListHead = NULL;
        sponsorListHead = NULL;
        root = NULL;
    }
};

// Test User struct
TEST_F(PublicTransportationSchedulerStructsTest, TestUserCreation) {
    User user;
    strcpy(user.username, "testuser");
    strcpy(user.password, "password");
    EXPECT_STREQ(user.username, "testuser");
    EXPECT_STREQ(user.password, "password");
}

// Test Band struct
TEST_F(PublicTransportationSchedulerStructsTest, TestBandCreation) {
    Band band;
    strcpy(band.name, "Test Band");
    EXPECT_STREQ(band.name, "Test Band");
}

// Test ScheduleNode creation and linking
TEST_F(PublicTransportationSchedulerStructsTest, TestScheduleNodeCreationAndLinking) {
    ScheduleNode* node1 = new ScheduleNode{ 1, "Band A", "2024-12-01", NULL, NULL };
    ScheduleNode* node2 = new ScheduleNode{ 2, "Band B", "2024-12-02", NULL, node1 };
    node1->next = node2;

    scheduleHead = node1;
    EXPECT_EQ(scheduleHead->scheduleID, 1);
    EXPECT_STREQ(scheduleHead->next->bandName, "Band B");

    delete node1;
    delete node2;
}

// Test TicketSale struct creation
TEST_F(PublicTransportationSchedulerStructsTest, TestTicketSaleCreation) {
    TicketSale sale = { 1, "Normal", 50.0, "2024-11-01" };
    EXPECT_EQ(sale.saleID, 1);
    EXPECT_STREQ(sale.ticketType, "Normal");
    EXPECT_FLOAT_EQ(sale.amount, 50.0);
    EXPECT_STREQ(sale.date, "2024-11-01");
}

// Test Vendor struct creation and linking
TEST_F(PublicTransportationSchedulerStructsTest, TestVendorCreationAndLinking) {
    Vendor* vendor1 = new Vendor{ 1, "Vendor A", "Food", NULL };
    Vendor* vendor2 = new Vendor{ 2, "Vendor B", "Drink", NULL };
    vendor1->next = vendor2;

    vendorListHead = vendor1;
    EXPECT_EQ(vendorListHead->id, 1);
    EXPECT_STREQ(vendorListHead->next->name, "Vendor B");

    delete vendor1;
    delete vendor2;
}

// Test Sponsor struct creation and linking
TEST_F(PublicTransportationSchedulerStructsTest, TestSponsorCreationAndLinking) {
    Sponsor* sponsor1 = new Sponsor{ 1, "Sponsor A", 1000.0, NULL };
    Sponsor* sponsor2 = new Sponsor{ 2, "Sponsor B", 2000.0, NULL };
    sponsor1->next = sponsor2;

    sponsorListHead = sponsor1;
    EXPECT_EQ(sponsorListHead->id, 1);
    EXPECT_DOUBLE_EQ(sponsorListHead->next->contributionAmount, 2000.0);

    delete sponsor1;
    delete sponsor2;
}

// Test DoubleNode struct for route linking
TEST_F(PublicTransportationSchedulerStructsTest, TestDoubleNodeCreationAndLinking) {
    DoubleNode* node1 = new DoubleNode{ 1, "Route A", "Start A", "End A", NULL, NULL };
    DoubleNode* node2 = new DoubleNode{ 2, "Route B", "Start B", "End B", NULL, node1 };
    node1->next = node2;

    EXPECT_EQ(node1->data, 1);
    EXPECT_STREQ(node1->next->routeName, "Route B");

    delete node1;
    delete node2;
}

// Test XORNode struct linking
TEST_F(PublicTransportationSchedulerStructsTest, TestXORNodeCreationAndLinking) {
    XORNode* node1 = new XORNode{ 1, NULL };
    XORNode* node2 = new XORNode{ 2, NULL };
    node1->npx = node2;
    node2->npx = node1;

    EXPECT_EQ(node1->data, 1);
    EXPECT_EQ(node1->npx, node2);

    delete node1;
    delete node2;
}

// Test SparseMatrixNode struct linking
TEST_F(PublicTransportationSchedulerStructsTest, TestSparseMatrixNodeCreationAndLinking) {
    SparseMatrixNode* node1 = new SparseMatrixNode{ 0, 0, 5, NULL };
    SparseMatrixNode* node2 = new SparseMatrixNode{ 1, 1, 10, NULL };
    node1->next = node2;

    EXPECT_EQ(node1->value, 5);
    EXPECT_EQ(node1->next->value, 10);

    delete node1;
    delete node2;
}

// Test Node struct for stack and queue operations
TEST_F(PublicTransportationSchedulerStructsTest, TestNodeStackAndQueueOperations) {
    Node* stackTop = NULL;
    Node* queueFront = NULL;
    Node* queueRear = NULL;

    // Stack test
    Node* stackNode = new Node{ 10, NULL };
    stackTop = stackNode;
    EXPECT_EQ(stackTop->data, 10);

    // Queue test
    Node* queueNode1 = new Node{ 20, NULL };
    queueFront = queueRear = queueNode1;
    Node* queueNode2 = new Node{ 30, NULL };
    queueRear->next = queueNode2;
    queueRear = queueNode2;

    EXPECT_EQ(queueFront->data, 20);
    EXPECT_EQ(queueRear->data, 30);

    delete stackNode;
    delete queueNode1;
    delete queueNode2;
}

// Test BPlusTreeNode struct creation
TEST_F(PublicTransportationSchedulerStructsTest, TestBPlusTreeNodeCreation) {
    BPlusTreeNode* node = new BPlusTreeNode;
    node->keys[0] = 1;
    node->sales[0] = new TicketSale{ 1, "Normal", 50.0, "2024-11-01" };
    node->numKeys = 1;
    node->isLeaf = true;

    root = node;
    EXPECT_EQ(root->keys[0], 1);
    EXPECT_STREQ(root->sales[0]->ticketType, "Normal");
    EXPECT_TRUE(root->isLeaf);

    delete root->sales[0];
    delete node;
}

// Complete flow test for registration and route addition
TEST_F(PublicTransportationSchedulerTest, TestCompleteFlow) {
    registerUser("flowuser", "flowpassword");
    EXPECT_EQ(login("flowuser", "flowpassword"), 1);
    addRoute(2, "Flow Route", "Flow Start", "Flow End");
    EXPECT_EQ(findDoubleNode(routeListHead, 2)->data, 2);
}
