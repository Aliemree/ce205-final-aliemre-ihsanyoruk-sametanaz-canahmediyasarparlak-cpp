#include "gtest/gtest.h"
#include "../../publictransportationscheduler/header/publictransportationscheduler.h"

// using namespace Coruh::PublicTransportationScheduler;  // Bu satırı kaldırıyoruz

class PublicTransportationSchedulerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Gerekli kurulum işlemleri
  }

  void TearDown() override {
    // Test sonrası temizleme işlemleri
  }
};

// Kullanıcı kayıt ve giriş işlemlerini test etme
TEST_F(PublicTransportationSchedulerTest, TestRegisterUser) {
  registerUser("testuser", "password");
  EXPECT_EQ(login("testuser", "password"), 1);  // Kayıt başarılı olmalı
}

TEST_F(PublicTransportationSchedulerTest, TestLoginInvalidUser) {
  EXPECT_EQ(login("invaliduser", "password"), 0);  // Geçersiz kullanıcı adı
}

// Güzergah ekleme ve gösterme işlemlerini test etme
TEST_F(PublicTransportationSchedulerTest, TestAddRoute) {
  addRoute(101);
  addRoute(102);
  EXPECT_EQ(routes[0], 101);
  EXPECT_EQ(routes[1], 102);
}

TEST_F(PublicTransportationSchedulerTest, TestRemoveRoute) {
  addRoute(101);
  addRoute(102);
  removeRoute(101);
  EXPECT_NE(routes[0], 101);  // 101 güzergahı silinmiş olmalı
}
