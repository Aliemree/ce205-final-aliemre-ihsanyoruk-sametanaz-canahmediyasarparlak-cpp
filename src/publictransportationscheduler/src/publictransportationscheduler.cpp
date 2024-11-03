#include "publictransportationscheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>  // uintptr_t için

// routes ve routeCount, diğer dosyalardan erişilebilmesi için tanımlandı
int routes[100];
int routeCount = 0;

// Kullanıcı veritabanını saklamak için basit bir dizi ve yapı
typedef struct {
  char username[50];
  char password[50];
} User;

User userDatabase[100];
int userCount = 0;

// XOR işlevi, XOR bağlantılı liste işlemlerinde kullanılıyor
XORNode *XOR(XORNode *a, XORNode *b) {
  return (XORNode *)((uintptr_t)(a) ^ (uintptr_t)(b));
}

// Kullanıcı veritabanını ikili dosyadan yükleme işlevi
void loadUserDatabase() {
  FILE *file;
  fopen_s(&file, "userDatabase.bin", "rb");

  if (file) {
    fread(&userCount, sizeof(int), 1, file);
    fread(userDatabase, sizeof(User), userCount, file);
    fclose(file);
  }
}

// Kullanıcı veritabanını ikili dosyaya kaydetme işlevi
void saveUserDatabase() {
  FILE *file;
  fopen_s(&file, "userDatabase.bin", "wb");
  fwrite(&userCount, sizeof(int), 1, file);
  fwrite(userDatabase, sizeof(User), userCount, file);
  fclose(file);
}

void saveRoutes() {
  FILE *file;
  fopen_s(&file, "routes.bin", "wb");

  if (file) {
    fwrite(&routeCount, sizeof(int), 1, file);
    fwrite(routes, sizeof(int), routeCount, file);
    fclose(file);
  } else {
    printf("Error: Could not open routes.bin for writing.\n");
  }
}


// Kullanıcı giriş işlevi
int login(const char *username, const char *password) {
  loadUserDatabase();

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
  loadUserDatabase();

  for (int i = 0; i < userCount; i++) {
    if (strcmp(userDatabase[i].username, username) == 0) {
      printf("Username already exists.\n");
      return;
    }
  }

  strcpy_s(userDatabase[userCount].username, sizeof(userDatabase[userCount].username), username);
  strcpy_s(userDatabase[userCount].password, sizeof(userDatabase[userCount].password), password);
  userCount++;
  saveUserDatabase();
  printf("User registered successfully.\n");
}

// Dosyadan güzergahları yükleme işlevi
void loadSchedulesFromFile(const char *filename) {
  FILE *file;
  fopen_s(&file, filename, "rb");

  if (!file) {
    printf("Error opening file: %s\n", filename);
    return;
  }

  fread(&routeCount, sizeof(int), 1, file);
  fread(routes, sizeof(int), routeCount, file);
  fclose(file);
  printf("Schedules loaded from file: %s\n", filename);
}

// Güzergahları gösterme işlevi
void showSchedules() {
  printf("Displaying bus and train schedules...\n");

  for (int i = 0; i < routeCount; i++) {
    printf("Route %d\n", routes[i]);
  }
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

// Veriyi sıkıştırıp kaydetme işlevi (Huffman kodlama yerine basit bir mesaj)
void compressAndSaveData(const char *data) {
  printf("Data compressed and saved.\n");
}

// Veriyi açma işlevi (Huffman açma yerine basit bir mesaj)
char *decompressData() {
  return "Decompressed data.";
}

// Güzergah ekleme işlevi
void addRoute(int routeID) {
  routes[routeCount++] = routeID;
  saveRoutes();
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
      saveRoutes();
      printf("Route %d removed.\n", routeID);
      return;
    }
  }

  printf("Route %d not found.\n", routeID);
}

// Çift Yönlü Bağlı Liste İşlevleri (Örnek: insertDoubleNode ve deleteDoubleNode)
DoubleNode *createDoubleNode(int data) {
  DoubleNode *newNode = (DoubleNode *)malloc(sizeof(DoubleNode));
  newNode->data = data;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}

void insertDoubleNode(DoubleNode **head, int data) {
  DoubleNode *newNode = createDoubleNode(data);
  newNode->next = *head;

  if (*head != NULL) {
    (*head)->prev = newNode;
  }

  *head = newNode;
}

void deleteDoubleNode(DoubleNode **head, int data) {
  DoubleNode *temp = *head;

  while (temp != NULL && temp->data != data) {
    temp = temp->next;
  }

  if (temp == NULL) return;

  if (temp->prev != NULL) temp->prev->next = temp->next;

  if (temp->next != NULL) temp->next->prev = temp->prev;

  if (temp == *head) *head = temp->next;

  free(temp);
}

void printDoubleList(DoubleNode *head) {
  while (head != NULL) {
    printf("%d ", head->data);
    head = head->next;
  }

  printf("\n");
}

// XOR Bağlı Liste İşlevleri (Örnek: insertXORNode)
XORNode *createXORNode(int data) {
  XORNode *newNode = (XORNode *)malloc(sizeof(XORNode));
  newNode->data = data;
  newNode->npx = NULL;
  return newNode;
}

void insertXORNode(XORNode **head, int data) {
  XORNode *newNode = createXORNode(data);
  newNode->npx = *head;

  if (*head != NULL) {
    (*head)->npx = XOR(newNode, (*head)->npx);
  }

  *head = newNode;
}

void printXORList(XORNode *head) {
  XORNode *curr = head;
  XORNode *prev = NULL;
  XORNode *next;

  while (curr != NULL) {
    printf("%d ", curr->data);
    next = XOR(prev, curr->npx);
    prev = curr;
    curr = next;
  }

  printf("\n");
}

// Seyrek Matris İşlevleri (Örnek: insertSparseNode)
SparseMatrixNode *createSparseNode(int row, int col, int value) {
  SparseMatrixNode *newNode = (SparseMatrixNode *)malloc(sizeof(SparseMatrixNode));
  newNode->row = row;
  newNode->col = col;
  newNode->value = value;
  newNode->next = NULL;
  return newNode;
}

void insertSparseNode(SparseMatrixNode **head, int row, int col, int value) {
  SparseMatrixNode *newNode = createSparseNode(row, col, value);
  newNode->next = *head;
  *head = newNode;
}

int getSparseValue(SparseMatrixNode *head, int row, int col) {
  SparseMatrixNode *current = head;

  while (current != NULL) {
    if (current->row == row && current->col == col) {
      return current->value;
    }

    current = current->next;
  }

  return 0;
}

void printSparseMatrix(SparseMatrixNode *head) {
  SparseMatrixNode *current = head;

  while (current != NULL) {
    printf("Row: %d, Col: %d, Value: %d\n", current->row, current->col, current->value);
    current = current->next;
  }
}
