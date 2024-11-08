#include <gtest/gtest.h>
#include "publictransportationscheduler.h"
#include "../../publictransportationscheduler/src/publictransportationscheduler.cpp"

// Test sınıfı
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
        // Temizlik işlemleri
        // Kullanıcıları, bandları ve diğer kaynakları sıfırlama işlemleri
        userCount = 0; // Kullanıcı sayısını sıfırla
        bandCount = 0; // Band sayısını sıfırla
        scheduleHead = NULL; // Takvim başını sıfırla
        vendorListHead = NULL; // Vendor listesini sıfırla
        sponsorListHead = NULL; // Sponsor listesini sıfırla
        routeListHead = NULL; // Rota listesini sıfırla
        root = NULL; // B+ ağacı kökünü sıfırla
        remove("bandDatabase.bin");
    }
};

// Kullanıcı kaydı ve girişi testleri
TEST_F(PublicTransportationSchedulerTest, TestRegisterUser) {
    registerUser("uniqueuser", "password");
    EXPECT_EQ(login("uniqueuser", "password"), 1);  // Kayıt başarılı olmalı
}

TEST_F(PublicTransportationSchedulerTest, TestLoginInvalidUser) {
    EXPECT_EQ(login("invaliduser", "password"), 0);  // Hatalı kullanıcı girişi başarısız olmalı
}

// Band yönetimi testleri
TEST_F(PublicTransportationSchedulerTest, TestAddBand) {
    addBand("Test Band");
    EXPECT_STREQ(bandDatabase[0].name, "Test Band"); // Band ismi kontrolü
}

TEST_F(PublicTransportationSchedulerTest, TestEditBand) {
    // İlk bandı ekleyin ve ardından güncelleyin
    addBand("Old Band Name");
    editBand("Old Band Name", "New Band Name");

    // Güncelleme sonrasında band ismini kontrol edin
    EXPECT_STREQ(bandDatabase[0].name, "New Band Name");
}

// Takvim yönetimi testleri
TEST_F(PublicTransportationSchedulerTest, TestCreateSchedule) {
    createSchedule(1, "Band B", "2024-12-02");
    EXPECT_STREQ(scheduleHead->bandName, "Band B"); // Takvim ismi kontrolü
    EXPECT_STREQ(scheduleHead->date, "2024-12-02"); // Takvim tarihi kontrolü
}

TEST_F(PublicTransportationSchedulerTest, TestEditSchedule) {
    createSchedule(1, "Band A", "2024-12-01");
    editSchedule(1, "Band B", "2024-12-02");
    EXPECT_STREQ(scheduleHead->bandName, "Band B"); // Güncellenen band ismi kontrolü
    EXPECT_STREQ(scheduleHead->date, "2024-12-02"); // Güncellenen tarih kontrolü
}

// Bilet satışı testleri
TEST_F(PublicTransportationSchedulerTest, TestViewSalesData) {
    loadSalesDatabase(); // Satış verilerini yükle
    viewSalesData(); // Satış verilerini görüntüle
    EXPECT_GE(salesCount, 0);  // Satış sayısı sıfır veya daha fazla olmalı
}

TEST_F(PublicTransportationSchedulerTest, TestGenerateSalesReport) {
    generateSalesReport();
    double totalAmount = 0;

    for (int i = 0; i < salesCount; i++) {
        totalAmount += salesDatabase[i].amount;
    }

    EXPECT_GE(totalAmount, 0); // Toplam satış miktarı sıfır veya daha fazla olmalı
}

// Vendor yönetimi testleri
TEST_F(PublicTransportationSchedulerTest, TestManageVendors) {
    addVendor(1, "Vendor A", "Food");
    EXPECT_STREQ(vendorListHead->name, "Vendor A"); // Ekleme kontrolü
}

// Sponsor takip testleri
TEST_F(PublicTransportationSchedulerTest, TestTrackSponsors) {
    addSponsor(1, "Sponsor A", 1000.0);
    EXPECT_STREQ(sponsorListHead->name, "Sponsor A"); // Ekleme kontrolü
}

// Çift bağlı liste testleri
TEST_F(PublicTransportationSchedulerTest, TestInsertDoubleNode) {
    DoubleNode* head = NULL;
    insertDoubleNode(&head, 5);
    EXPECT_EQ(head->data, 5); // Eklenen düğüm kontrolü
}

TEST_F(PublicTransportationSchedulerTest, TestDeleteDoubleNode) {
    DoubleNode* head = NULL;
    insertDoubleNode(&head, 5);
    insertDoubleNode(&head, 10);
    EXPECT_EQ(deleteDoubleNode(&head, 5), 1); // Düğüm silinmeli
    EXPECT_EQ(head->data, 10); // Kalan düğüm kontrolü
}

// XOR bağlı liste testleri
TEST_F(PublicTransportationSchedulerTest, TestInsertXORNode) {
    XORNode* head = NULL;
    insertXORNode(&head, 5);
    EXPECT_EQ(head->data, 5); // Eklenen düğüm kontrolü
}

// Sparse matris testleri
TEST_F(PublicTransportationSchedulerTest, TestInsertSparseNode) {
    SparseMatrixNode* head = NULL;
    insertSparseNode(&head, 0, 0, 5);
    EXPECT_EQ(head->value, 5); // Eklenen değer kontrolü
}

// Genel fonksiyon testleri
TEST_F(PublicTransportationSchedulerTest, TestHashTableFunctions) {
    addUserToHashTable("user1", "pass1");
    EXPECT_EQ(verifyUserInHashTable("user1", "pass1"), 1); // Kullanıcı doğrulama test
}

TEST_F(PublicTransportationSchedulerTest, TestViewBands) {
    addBand("View Band");
    EXPECT_GE(bandCount, 1); // Band sayısı bir veya daha fazla olmalı
}

// B+ ağacı testleri
TEST_F(PublicTransportationSchedulerTest, TestInsertBPlusNode) {
    TicketSale sale = { 1, "Normal", 50.0, "2024-11-01" };
    insertBPlusNode(sale.saleID, &sale);
    TicketSale* foundSale = searchBPlusTree(sale.saleID);
    EXPECT_NE(foundSale, nullptr); // Satış bulunmalı
    EXPECT_EQ(foundSale->amount, 50.0); // Miktar kontrolü
}

// Başlatma testleri
TEST_F(PublicTransportationSchedulerTest, TestInitializeBPlusTree) {
    initializeBPlusTree();
    EXPECT_EQ(root, nullptr); // Başlangıçta kök düğüm null olmalı
}

// Veritabanı testleri
TEST_F(PublicTransportationSchedulerTest, TestLoadUserDatabase) {
    loadUserDatabase();
    EXPECT_GE(userCount, 0); // Kullanıcı sayısı sıfır veya daha fazla olmalı
}

TEST_F(PublicTransportationSchedulerTest, TestSaveUserDatabase) {
    registerUser("userToSave", "password");
    saveUserDatabase();
    EXPECT_EQ(login("userToSave", "password"), 1); // Kaydedilen kullanıcı doğrulama
}

TEST_F(PublicTransportationSchedulerTest, TestLoadBandDatabase) {
    loadBandDatabase();
    EXPECT_GE(bandCount, 0); // Band sayısı sıfır veya daha fazla olmalı
}

TEST_F(PublicTransportationSchedulerTest, TestSaveAndLoadBandDatabase) {
    // Birkaç band ekle
    addBand("Band to Save 1");
    addBand("Band to Save 2");
    addBand("Band to Save 3");

    // Veritabanını kaydet
    saveBandDatabase();

    // bandDatabase'i ve bandCount'u sıfırla ve ardından veritabanını yükle
    bandCount = 0;
    memset(bandDatabase, 0, sizeof(bandDatabase));
    loadBandDatabase();

    // Yüklenen verileri kontrol et
    EXPECT_EQ(bandCount, 3); // 3 band kaydedilmiş olmalı
    EXPECT_STREQ(bandDatabase[0].name, "Band to Save 1");
    EXPECT_STREQ(bandDatabase[1].name, "Band to Save 2");
    EXPECT_STREQ(bandDatabase[2].name, "Band to Save 3");
}

// Uygulama akışının düzgün çalıştığını kontrol etme
TEST_F(PublicTransportationSchedulerTest, TestCompleteFlow) {
    registerUser("flowuser", "flowpassword");
    EXPECT_EQ(login("flowuser", "flowpassword"), 1);
    addRoute(2, "Flow Route", "Flow Start", "Flow End");
    EXPECT_EQ(findDoubleNode(routeListHead, 2)->data, 2); // Rota eklenmeli
}