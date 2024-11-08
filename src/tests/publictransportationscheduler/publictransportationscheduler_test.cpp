#include <gtest/gtest.h>
#include "publictransportationscheduler.h"
#include "../../publictransportationscheduler/src/publictransportationscheduler.cpp"

// Test class setup for main functionality
class PublicTransportationSchedulerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    initializeHashTable();
    vendorListHead = NULL;
    sponsorListHead = NULL;
    scheduleHead = NULL;
    routeListHead = NULL;
    root = NULL;
    userCount = 0;
    bandCount = 0;
    loadBandDatabase();
    scheduleCount = 0;
    salesCount = 0;
    vendorCount = 0;
    sponsorCount = 0;
    memset(bandDatabase, 0, sizeof(bandDatabase));
  }

  void TearDown() override {
    routeListHead = NULL;
    scheduleHead = NULL;
    vendorListHead = NULL;
    sponsorListHead = NULL;
    root = NULL;
  }
};

TEST(PublicTransportationSchedulerTest, TestGlobalDefinitionsInitialization) {
    EXPECT_EQ(userCount, 0);
    EXPECT_EQ(bandCount, 0);
    EXPECT_EQ(scheduleCount, 0);
    EXPECT_EQ(salesCount, 0);
    EXPECT_EQ(vendorCount, 0);
    EXPECT_EQ(sponsorCount, 0);
    EXPECT_EQ(routeListHead, nullptr);
    EXPECT_EQ(heapSize, 0);
    for (int i = 0; i < TABLE_SIZE; ++i) {
        EXPECT_EQ(hashTable[i], nullptr);
    }
}

TEST(PublicTransportationSchedulerTest, TestAddUserToHashTable) {
    addUserToHashTable("testuser", "password123");
    int index = hashFunction("testuser");
    ASSERT_NE(hashTable[index], nullptr);
    EXPECT_STREQ(hashTable[index]->username, "testuser");
    EXPECT_STREQ(hashTable[index]->password, "password123");
}
// Global Definitions Testleri
//TEST(GlobalDefinitionsTest, TestUserDatabase) {
//  // Kullanıcı ekleme işlemi
//  strcpy(userDatabase[userCount].username, "testuser");
//  strcpy(userDatabase[userCount].password, "testpass");
//  userCount++;
//  // Doğru kaydedilip kaydedilmediğini kontrol et
//  EXPECT_EQ(userCount, 1);
//  EXPECT_STREQ(userDatabase[0].username, "testuser");
//  EXPECT_STREQ(userDatabase[0].password, "testpass");
//}

//TEST(GlobalDefinitionsTest, TestBandDatabase) {
//  // Band ekleme işlemi
//  strcpy(bandDatabase[bandCount].name, "Test Band");
//  bandCount++;
//  // Doğru kaydedilip kaydedilmediğini kontrol et
//  EXPECT_EQ(bandCount, 1);
//  EXPECT_STREQ(bandDatabase[0].name, "Test Band");
//}

TEST(GlobalDefinitionsTest, TestScheduleDatabase) {
  // Program ekleme işlemi
  scheduleDatabase[scheduleCount].scheduleID = 1;
  strcpy(scheduleDatabase[scheduleCount].bandName, "Band 1");
  strcpy(scheduleDatabase[scheduleCount].date, "2024-11-10");
  scheduleCount++;
  // Doğru kaydedilip kaydedilmediğini kontrol et
  EXPECT_EQ(scheduleCount, 1);
  EXPECT_EQ(scheduleDatabase[0].scheduleID, 1);
  EXPECT_STREQ(scheduleDatabase[0].bandName, "Band 1");
  EXPECT_STREQ(scheduleDatabase[0].date, "2024-11-10");
}

TEST(GlobalDefinitionsTest, TestSalesDatabase) {
  // Satış ekleme işlemi
  salesDatabase[salesCount].saleID = 1;
  strcpy(salesDatabase[salesCount].ticketType, "Normal");
  salesDatabase[salesCount].amount = 50.0;
  strcpy(salesDatabase[salesCount].date, "2024-11-01");
  salesCount++;
  // Doğru kaydedilip kaydedilmediğini kontrol et
  EXPECT_EQ(salesCount, 1);
  EXPECT_EQ(salesDatabase[0].saleID, 1);
  EXPECT_STREQ(salesDatabase[0].ticketType, "Normal");
  EXPECT_FLOAT_EQ(salesDatabase[0].amount, 50.0);
  EXPECT_STREQ(salesDatabase[0].date, "2024-11-01");
}

TEST(GlobalDefinitionsTest, TestVendorDatabase) {
  // Tedarikçi ekleme işlemi
  vendorDatabase[vendorCount].id = 1;
  strcpy(vendorDatabase[vendorCount].name, "Vendor 1");
  strcpy(vendorDatabase[vendorCount].serviceType, "Food");
  vendorCount++;
  // Doğru kaydedilip kaydedilmediğini kontrol et
  EXPECT_EQ(vendorCount, 1);
  EXPECT_EQ(vendorDatabase[0].id, 1);
  EXPECT_STREQ(vendorDatabase[0].name, "Vendor 1");
  EXPECT_STREQ(vendorDatabase[0].serviceType, "Food");
}

TEST(GlobalDefinitionsTest, TestSponsorDatabase) {
  // Sponsor ekleme işlemi
  sponsorDatabase[sponsorCount].id = 1;
  strcpy(sponsorDatabase[sponsorCount].name, "Sponsor 1");
  sponsorDatabase[sponsorCount].contributionAmount = 1000.0;
  sponsorCount++;
  // Doğru kaydedilip kaydedilmediğini kontrol et
  EXPECT_EQ(sponsorCount, 1);
  EXPECT_EQ(sponsorDatabase[0].id, 1);
  EXPECT_STREQ(sponsorDatabase[0].name, "Sponsor 1");
  EXPECT_DOUBLE_EQ(sponsorDatabase[0].contributionAmount, 1000.0);
}

// Route Linked List Test
TEST(GlobalDefinitionsTest, TestRouteListHead) {
  // Yeni rota ekleme
  DoubleNode* newRoute = new DoubleNode;
  newRoute->data = 1;
  strcpy(newRoute->routeName, "Route 1");
  strcpy(newRoute->startPoint, "Start Point");
  strcpy(newRoute->endPoint, "End Point");
  newRoute->next = nullptr;
  newRoute->prev = nullptr;
  routeListHead = newRoute;
  // Doğru eklenip eklenmediğini kontrol et
  ASSERT_NE(routeListHead, nullptr);
  EXPECT_EQ(routeListHead->data, 1);
  EXPECT_STREQ(routeListHead->routeName, "Route 1");
  EXPECT_STREQ(routeListHead->startPoint, "Start Point");
  EXPECT_STREQ(routeListHead->endPoint, "End Point");
  delete newRoute;  // Hafıza sızıntısını önlemek için serbest bırakın
}

// Hash Table Tests
TEST(HashTableTest, TestAddUserToHashTable) {
  // Hash tablosunda bir kullanıcı ekleyin
  User* user = new User;
  strcpy(user->username, "testuser");
  strcpy(user->password, "testpass");
  // Hash tablosuna kullanıcıyı ekleyin
  int hashIndex = hashFunction(user->username);
  hashTable[hashIndex] = user;
  // Kullanıcının doğru şekilde eklendiğini kontrol edin
  ASSERT_NE(hashTable[hashIndex], nullptr);
  EXPECT_STREQ(hashTable[hashIndex]->username, "testuser");
  EXPECT_STREQ(hashTable[hashIndex]->password, "testpass");
  delete user;  // Bellek sızıntısını önlemek için kullanıcıyı serbest bırakın
}

TEST(HashTableTest, TestUserNotInHashTable) {
  // Var olmayan bir kullanıcıyı kontrol edin
  int hashIndex = hashFunction("nonexistent");
  EXPECT_EQ(hashTable[hashIndex], nullptr);
}

// Route Struct Test
TEST(RouteStructTest, TestRouteCreation) {
  // Bir route nesnesi oluşturun ve alanları doldurun
  Route route;
  route.routeID = 1;
  strcpy(route.routeName, "Main Route");
  // Route bilgilerini doğrulayın
  EXPECT_EQ(route.routeID, 1);
  EXPECT_STREQ(route.routeName, "Main Route");
}

// Stack Tests
TEST(StackTest, TestPushAndPop) {
  // İlk olarak stack'in boş olduğunu doğrula
  EXPECT_EQ(stack, nullptr);
  // Stack'e bir eleman ekle
  push(10);
  EXPECT_NE(stack, nullptr);  // Stack'in boş olmadığını doğrula
  EXPECT_EQ(stack->data, 10); // Eklenen ilk elemanın doğru olduğunu doğrula
  // Stack'e başka bir eleman daha ekle
  push(20);
  EXPECT_EQ(stack->data, 20); // Son eklenen elemanın en üstte olduğunu doğrula
  // İlk elemanı çıkar ve değerini kontrol et
  int poppedValue = pop();
  EXPECT_EQ(poppedValue, 20);
  // İkinci elemanı da çıkar ve kontrol et
  poppedValue = pop();
  EXPECT_EQ(poppedValue, 10);
  // Stack boş olmalı, dolayısıyla -1 döndürmeli
  poppedValue = pop();
  EXPECT_EQ(poppedValue, -1);
}

// Queue Tests
TEST(QueueTest, TestEnqueueAndDequeue) {
  // İlk olarak queue'nun boş olduğunu doğrula
  EXPECT_EQ(queueFront, nullptr);
  EXPECT_EQ(queueRear, nullptr);
  // Queue'ya eleman ekle
  enqueue(30);
  EXPECT_NE(queueFront, nullptr);  // Queue'nun boş olmadığını doğrula
  EXPECT_NE(queueRear, nullptr);
  EXPECT_EQ(queueFront->data, 30); // İlk elemanın doğru olduğunu doğrula
  // Queue'ya başka bir eleman daha ekle
  enqueue(40);
  EXPECT_EQ(queueRear->data, 40);  // Son eklenen elemanın kuyrukta olduğunu doğrula
  // İlk elemanı çıkar ve değerini kontrol et
  int dequeuedValue = dequeue();
  EXPECT_EQ(dequeuedValue, 30);
  // İkinci elemanı da çıkar ve kontrol et
  dequeuedValue = dequeue();
  EXPECT_EQ(dequeuedValue, 40);
  // Queue boş olmalı, dolayısıyla -1 döndürmeli
  dequeuedValue = dequeue();
  EXPECT_EQ(dequeuedValue, -1);
}

// Priority Queue (Heap) Tests
TEST(HeapTest, TestInsertAndExtractMin) {
  // Başlangıçta heap boş olmalı
  EXPECT_EQ(heapSize, 0);
  // Heap'e eleman ekle ve boyutu kontrol et
  insertHeap(50);
  EXPECT_EQ(heapSize, 1);
  EXPECT_EQ(heap[0], 50);  // Eklenen ilk elemanın minimum olduğunu doğrula
  // Başka elemanlar ekle
  insertHeap(30);
  EXPECT_EQ(heapSize, 2);
  EXPECT_EQ(heap[0], 30);  // En küçük eleman güncellenmeli
  insertHeap(40);
  EXPECT_EQ(heapSize, 3);
  EXPECT_EQ(heap[0], 30);  // Minimum eleman hala 30 olmalı
  // Minimum elemanı çıkar ve doğru değeri döndürdüğünü doğrula
  int minVal = extractMin();
  EXPECT_EQ(minVal, 30);
  EXPECT_EQ(heapSize, 2);
  // Sonraki minimum elemanı çıkar
  minVal = extractMin();
  EXPECT_EQ(minVal, 40);
  EXPECT_EQ(heapSize, 1);
  // Kalan elemanı çıkar
  minVal = extractMin();
  EXPECT_EQ(minVal, 50);
  EXPECT_EQ(heapSize, 0);
  // Heap boş olmalı, bu yüzden -1 döndürmeli
  minVal = extractMin();
  EXPECT_EQ(minVal, -1);
}

// Test User struct
TEST(PublicTransportationSchedulerStructTest, TestUserStruct) {
  User user;
  strcpy(user.username, "testuser");
  strcpy(user.password, "password");
  EXPECT_STREQ(user.username, "testuser");
  EXPECT_STREQ(user.password, "password");
}

// Test Band struct
TEST(PublicTransportationSchedulerStructTest, TestBandStruct) {
  Band band;
  strcpy(band.name, "Test Band");
  EXPECT_STREQ(band.name, "Test Band");
}

// Test ScheduleNode struct creation and linking
TEST(PublicTransportationSchedulerStructTest, TestScheduleNodeStruct) {
  ScheduleNode* node1 = new ScheduleNode{ 1, "Band A", "2024-12-01", nullptr, nullptr };
  ScheduleNode* node2 = new ScheduleNode{ 2, "Band B", "2024-12-02", nullptr, node1 };
  node1->next = node2;
  EXPECT_EQ(node1->scheduleID, 1);
  EXPECT_STREQ(node1->bandName, "Band A");
  EXPECT_EQ(node1->next, node2);
  delete node1;
  delete node2;
}

// Test TicketSale struct creation
TEST(PublicTransportationSchedulerStructTest, TestTicketSaleStruct) {
  TicketSale sale = { 1, "Normal", 50.0, "2024-11-01" };
  EXPECT_EQ(sale.saleID, 1);
  EXPECT_STREQ(sale.ticketType, "Normal");
  EXPECT_FLOAT_EQ(sale.amount, 50.0);
  EXPECT_STREQ(sale.date, "2024-11-01");
}

// Test Vendor struct creation and linking
TEST(PublicTransportationSchedulerStructTest, TestVendorStruct) {
  Vendor* vendor1 = new Vendor{ 1, "Vendor A", "Food", nullptr };
  Vendor* vendor2 = new Vendor{ 2, "Vendor B", "Drink", nullptr };
  vendor1->next = vendor2;
  EXPECT_EQ(vendor1->id, 1);
  EXPECT_STREQ(vendor1->name, "Vendor A");
  EXPECT_STREQ(vendor1->serviceType, "Food");
  EXPECT_EQ(vendor1->next, vendor2);
  delete vendor1;
  delete vendor2;
}

// Test DoubleNode struct for route creation and linking
TEST(PublicTransportationSchedulerStructTest, TestDoubleNodeStruct) {
  DoubleNode* node1 = new DoubleNode{ 1, "Route A", "Start A", "End A", nullptr, nullptr };
  DoubleNode* node2 = new DoubleNode{ 2, "Route B", "Start B", "End B", nullptr, node1 };
  node1->next = node2;
  EXPECT_EQ(node1->data, 1);
  EXPECT_STREQ(node1->routeName, "Route A");
  EXPECT_EQ(node1->next, node2);
  delete node1;
  delete node2;
}

// Test XORNode struct linking
TEST(PublicTransportationSchedulerStructTest, TestXORNodeStruct) {
  XORNode* node1 = new XORNode{ 1, nullptr };
  XORNode* node2 = new XORNode{ 2, nullptr };
  node1->npx = node2;
  node2->npx = node1;
  EXPECT_EQ(node1->data, 1);
  EXPECT_EQ(node1->npx, node2);
  EXPECT_EQ(node2->npx, node1);
  delete node1;
  delete node2;
}

// Test SparseMatrixNode struct creation and linking
TEST(PublicTransportationSchedulerStructTest, TestSparseMatrixNodeStruct) {
  SparseMatrixNode* node1 = new SparseMatrixNode{ 0, 1, 5, nullptr };
  SparseMatrixNode* node2 = new SparseMatrixNode{ 1, 2, 10, nullptr };
  node1->next = node2;
  EXPECT_EQ(node1->value, 5);
  EXPECT_EQ(node1->next->value, 10);
  delete node1;
  delete node2;
}

// Band Management Test
TEST(PublicTransportationSchedulerTest, TestEditBand) {
  addBand("OldBand");
  editBand("OldBand", "NewBand");
  // BandDatabase'in ilk elemanında beklenen ismi doğrulayın
  ASSERT_GT(bandCount, 0); // bandCount sıfırdan büyük olmalı
  EXPECT_STREQ(bandDatabase[0].name, "NewBand");
}

// Test Sponsor struct creation and linking
TEST(PublicTransportationSchedulerStructTest, TestSponsorStruct) {
  Sponsor* sponsor1 = new Sponsor{ 1, "Sponsor A", 1000.0, nullptr };
  Sponsor* sponsor2 = new Sponsor{ 2, "Sponsor B", 2000.0, nullptr };
  sponsor1->next = sponsor2;
  EXPECT_EQ(sponsor1->id, 1);
  EXPECT_STREQ(sponsor1->name, "Sponsor A");
  EXPECT_DOUBLE_EQ(sponsor1->contributionAmount, 1000.0);
  EXPECT_EQ(sponsor1->next, sponsor2);
  delete sponsor1;
  delete sponsor2;
}

// Test user creation and hash table functions
//TEST(PublicTransportationSchedulerTest, TestHashTableFunctions) {
//  addUserToHashTable("testuser", "testpass");
//  EXPECT_EQ(verifyUserInHashTable("testuser", "testpass"), 1);
//  EXPECT_EQ(verifyUserInHashTable("nonexistent", "testpass"), 0);
//}

// Test adding and finding a route in double linked list
TEST(PublicTransportationSchedulerTest, TestAddAndFindRoute) {
  addRoute(1, "Route1", "Start1", "End1");
  DoubleNode* node = findDoubleNode(routeListHead, 1);
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->data, 1);
  EXPECT_STREQ(node->routeName, "Route1");
}

// Test deleting a route
//TEST_F(PublicTransportationSchedulerTest, TestDeleteRoute) {
//  addRoute(1, "Route1", "Start1", "End1");
//  EXPECT_EQ(deleteDoubleNode(&routeListHead, 1), 1);
//  EXPECT_EQ(findDoubleNode(routeListHead, 1), nullptr);
//}

// Test XOR linked list insertion
TEST(PublicTransportationSchedulerTest, TestInsertXORNode) {
  XORNode* head = NULL;
  insertXORNode(&head, 1);
  insertXORNode(&head, 2);
  EXPECT_EQ(head->data, 2);
  EXPECT_EQ(head->npx->data, 1);
}

// Test inserting a node in sparse matrix
TEST(PublicTransportationSchedulerTest, TestInsertSparseNode) {
  SparseMatrixNode* head = NULL;
  insertSparseNode(&head, 0, 1, 5);
  EXPECT_EQ(head->row, 0);
  EXPECT_EQ(head->col, 1);
  EXPECT_EQ(head->value, 5);
}

// Test stack operations
TEST(PublicTransportationSchedulerTest, TestStackOperations) {
  push(10);
  push(20);
  EXPECT_EQ(pop(), 20);
  EXPECT_EQ(pop(), 10);
  EXPECT_EQ(pop(), -1);
}

// Test queue operations
TEST(PublicTransportationSchedulerTest, TestQueueOperations) {
  enqueue(30);
  enqueue(40);
  EXPECT_EQ(dequeue(), 30);
  EXPECT_EQ(dequeue(), 40);
  EXPECT_EQ(dequeue(), -1);
}

// Test heap operations
TEST(PublicTransportationSchedulerTest, TestHeapOperations) {
  insertHeap(30);
  insertHeap(10);
  insertHeap(20);
  EXPECT_EQ(extractMin(), 10);
  EXPECT_EQ(extractMin(), 20);
  EXPECT_EQ(extractMin(), 30);
}

// Test band management functions


// Test schedule management functions
TEST(PublicTransportationSchedulerTest, TestScheduleManagement) {
  createSchedule(1, "Band A", "2024-11-10");
  EXPECT_EQ(scheduleHead->scheduleID, 1);
  EXPECT_STREQ(scheduleHead->bandName, "Band A");
  EXPECT_STREQ(scheduleHead->date, "2024-11-10");
  editSchedule(1, "Band B", "2024-11-15");
  EXPECT_STREQ(scheduleHead->bandName, "Band B");
  EXPECT_STREQ(scheduleHead->date, "2024-11-15");
  EXPECT_EQ(deleteSchedule(1), 1);
}

// Test vendor and sponsor management
TEST(PublicTransportationSchedulerTest, TestVendorAndSponsorManagement) {
  addVendor(1, "Vendor A", "Food");
  EXPECT_EQ(vendorListHead->id, 1);
  EXPECT_STREQ(vendorListHead->name, "Vendor A");
  addSponsor(1, "Sponsor A", 1000.0);
  EXPECT_EQ(sponsorListHead->id, 1);
  EXPECT_DOUBLE_EQ(sponsorListHead->contributionAmount, 1000.0);
}

// B+ tree operations for ticket sales
TEST(PublicTransportationSchedulerTest, TestBPlusTreeOperations) {
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
TEST(PublicTransportationSchedulerTest, TestGenerateSalesReport) {
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
TEST(PublicTransportationSchedulerTest, TestCompleteFlow) {
  registerUser("flowuser", "flowpassword");
  EXPECT_EQ(login("flowuser", "flowpassword"), 1);
  addRoute(2, "Flow Route", "Flow Start", "Flow End");
  EXPECT_EQ(findDoubleNode(routeListHead, 2)->data, 2);
}
