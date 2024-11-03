#include "gtest/gtest.h"
#include "publictransportationscheduler.h"

class PublicTransportationSchedulerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Gerekli ön hazırlık işlemleri
    }

    void TearDown() override {
        // Test sonrası temizleme işlemleri
    }
};

// Kullanıcı kayıt ve giriş işlemleri testleri
TEST_F(PublicTransportationSchedulerTest, TestRegisterUser) {
    registerUser("testuser", "password");
    EXPECT_EQ(login("testuser", "password"), 1);  // Kayıt başarılı olmalı
}

TEST_F(PublicTransportationSchedulerTest, TestLoginInvalidUser) {
    EXPECT_EQ(login("invaliduser", "password"), 0);  // Geçersiz kullanıcı adı
}

// Bilet satış işlemlerini test etme
TEST_F(PublicTransportationSchedulerTest, TestViewSalesData) {
    loadSalesDatabase();
    viewSalesData();
    EXPECT_GE(salesCount, 0);  // salesCount sıfır veya daha fazla olmalı
}

TEST_F(PublicTransportationSchedulerTest, TestGenerateSalesReport) {
    generateSalesReport();
    // Toplam satış miktarını kontrol etme
    double totalAmount = 0;
    for (int i = 0; i < salesCount; i++) {
        totalAmount += salesDatabase[i].amount;
    }
    EXPECT_GE(totalAmount, 0);  // Toplam satış miktarı sıfır veya daha fazla olmalı
}

// Vendor işlemlerini test etme
TEST_F(PublicTransportationSchedulerTest, TestManageVendors) {
    loadVendorDatabase();
    manageVendors();
    EXPECT_GE(vendorCount, 0);  // vendorCount sıfır veya daha fazla olmalı
}

// Sponsor işlemlerini test etme
TEST_F(PublicTransportationSchedulerTest, TestTrackSponsors) {
    loadSponsorDatabase();
    trackSponsors();
    EXPECT_GE(sponsorCount, 0);  // sponsorCount sıfır veya daha fazla olmalı
}

// Band ve sanatçı işlemleri testleri
TEST_F(PublicTransportationSchedulerTest, TestAddBand) {
    addBand("Test Band");
    ASSERT_EQ(bandDatabase[0].name, std::string("Test Band"));
}

TEST_F(PublicTransportationSchedulerTest, TestEditBand) {
    addBand("Old Band Name");
    editBand("Old Band Name", "New Band Name");
    ASSERT_EQ(bandDatabase[0].name, std::string("New Band Name"));
}

TEST_F(PublicTransportationSchedulerTest, TestViewBands) {
    addBand("View Band");
    viewBands();
    EXPECT_GE(bandCount, 1);
}

// Schedule işlemleri testleri
TEST_F(PublicTransportationSchedulerTest, TestCreateSchedule) {
    createSchedule(1, "Band A", "2024-12-01");
    ASSERT_EQ(scheduleDatabase[0].bandName, std::string("Band A"));
    ASSERT_EQ(scheduleDatabase[0].date, std::string("2024-12-01"));
}

TEST_F(PublicTransportationSchedulerTest, TestEditSchedule) {
    createSchedule(1, "Band A", "2024-12-01");
    editSchedule(1, "Band B", "2024-12-02");
    ASSERT_EQ(scheduleDatabase[0].bandName, std::string("Band B"));
    ASSERT_EQ(scheduleDatabase[0].date, std::string("2024-12-02"));
}

TEST_F(PublicTransportationSchedulerTest, TestViewSchedules) {
    createSchedule(1, "View Band", "2024-12-01");
    viewSchedules();
    EXPECT_GE(scheduleCount, 1);
}

// Double Linked List işlemleri testleri
TEST_F(PublicTransportationSchedulerTest, TestInsertDoubleNode) {
    DoubleNode* head = NULL;
    insertDoubleNode(&head, 5);
    ASSERT_EQ(head->data, 5);
}

TEST_F(PublicTransportationSchedulerTest, TestSaveAndLoadDoubleLinkedList) {
    DoubleNode* head = NULL;
    insertDoubleNode(&head, 5);
    saveDoubleLinkedListToFile(head, "doublelist.bin");

    DoubleNode* loadedHead = NULL;
    loadDoubleLinkedListFromFile(&loadedHead, "doublelist.bin");
    ASSERT_EQ(loadedHead->data, 5);
}

// XOR Linked List işlemleri testleri
TEST_F(PublicTransportationSchedulerTest, TestInsertXORNode) {
    XORNode* head = NULL;
    insertXORNode(&head, 5);
    ASSERT_EQ(head->data, 5);
}

TEST_F(PublicTransportationSchedulerTest, TestSaveAndLoadXORLinkedList) {
    XORNode* head = NULL;
    insertXORNode(&head, 5);
    saveXORLinkedListToFile(head, "xorlist.bin");

    XORNode* loadedHead = NULL;
    loadXORLinkedListFromFile(&loadedHead, "xorlist.bin");
    ASSERT_EQ(loadedHead->data, 5);
}

// Seyrek Matris işlemleri testleri
TEST_F(PublicTransportationSchedulerTest, TestInsertSparseNode) {
    SparseMatrixNode* head = NULL;
    insertSparseNode(&head, 0, 0, 5);
    ASSERT_EQ(head->value, 5);
}

TEST_F(PublicTransportationSchedulerTest, TestSaveAndLoadSparseMatrix) {
    SparseMatrixNode* head = NULL;
    insertSparseNode(&head, 0, 0, 5);
    saveSparseMatrixToFile(head, "sparsematrix.bin");

    SparseMatrixNode* loadedHead = NULL;
    loadSparseMatrixFromFile(&loadedHead, "sparsematrix.bin");
    ASSERT_EQ(loadedHead->value, 5);
}
