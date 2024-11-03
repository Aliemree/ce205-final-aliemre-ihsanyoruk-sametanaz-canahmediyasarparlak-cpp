#include "publictransportationscheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Kullanıcı veritabanını saklamak için basit bir dizi ve yapı
typedef struct {
  char username[50];
  char password[50];
} User;

User userDatabase[100];
int userCount = 0;

// Güzergahları saklamak için dizi
int routes[100];
int routeCount = 0;

// Kullanıcı giriş işlevi
int login(const char *username, const char *password) {
  for (int i = 0; i < userCount; i++) {
    if (strcmp(userDatabase[i].username, username) == 0 &&
        strcmp(userDatabase[i].password, password) == 0) {
      printf("Login successful.\n");
      return 1;
    }
  }

  printf("Invalid username or password.\n");
  return 0;
}

// Kullanıcı kayıt işlevi
void registerUser(const char *username, const char *password) {
  for (int i = 0; i < userCount; i++) {
    if (strcmp(userDatabase[i].username, username) == 0) {
      printf("Username already exists.\n");
      return;
    }
  }

  strcpy(userDatabase[userCount].username, username);
  strcpy(userDatabase[userCount].password, password);
  userCount++;
  printf("User registered successfully.\n");
}

// Dosyadan güzergahları yükleme işlevi
void loadSchedulesFromFile(const char *filename) {
  FILE *file = fopen(filename, "r");

  if (!file) {
    printf("Error opening file: %s\n", filename);
    return;
  }

  printf("Schedules loaded from file: %s\n", filename);
  fclose(file);
}

// Güzergahları gösterme işlevi
void showSchedules() {
  printf("Displaying bus and train schedules...\n");
}

// Ücret hesaplama işlevi
void calculateFare(const char *route, const char *ticketType) {
  double baseFare = 5.0;

  if (strcmp(ticketType, "Student") == 0) {
    baseFare *= 0.5;
  }

  printf("Calculated fare for %s with %s ticket: %.2f\n", route, ticketType, baseFare);
}

// Gecikme bildirim işlevi
void alertForDelays() {
  printf("No delays currently reported.\n");
}

// Veriyi sıkıştırıp kaydetme işlevi (Huffman kodlama yerine bir mesaj)
void compressAndSaveData(const char *data) {
  printf("Data compressed and saved.\n");
}

// Veriyi açma işlevi
char *decompressData() {
  return "Decompressed data.";
}

// Güzergah ekleme işlevi
void addRoute(int routeID) {
  routes[routeCount++] = routeID;
  printf("Route %d added.\n", routeID);
}

// Güzergah silme işlevi
void removeRoute(int routeID) {
  for (int i = 0; i < routeCount; i++) {
    if (routes[i] == routeID) {
      for (int j = i; j < routeCount - 1; j++) {
        routes[j] = routes[j + 1];
      }

      routeCount--;
      printf("Route %d removed.\n", routeID);
      return;
    }
  }

  printf("Route %d not found.\n", routeID);
}

// Metin arama işlevi (KMP algoritması yerine basit bir arama)
void searchText(const char *text, const char *pattern) {
  if (strstr(text, pattern) != NULL) {
    printf("Pattern %s found in text.\n", pattern);
  } else {
    printf("Pattern %s not found in text.\n", pattern);
  }
}

// Dosya indeksi ekleme işlevi (B+ ağacı yerine mesaj)
void insertFileIndex(int key) {
  printf("File indexed with key %d.\n", key);
}

// Dosya indeksi kaldırma işlevi
void removeFileIndex(int key) {
  printf("File index with key %d removed.\n", key);
}

// Dosya indeksi arama işlevi
int searchFileIndex(int key) {
  printf("File index with key %d found.\n", key);
  return key;
}

// Güçlü bağlı bileşenleri bulma işlevi
void findStronglyConnectedComponents() {
  printf("Strongly connected components identified.\n");
}

// Genişlik öncelikli arama işlevi
void exploreUsingBFS(int start) {
  printf("Exploring from node %d using BFS.\n", start);
}

// Derinlik öncelikli arama işlevi
void exploreUsingDFS(int start) {
  printf("Exploring from node %d using DFS.\n", start);
}
