#ifndef PUBLICTRANSPORTATIONSCHEDULER_H
#define PUBLICTRANSPORTATIONSCHEDULER_H

#include <stdio.h>
#include <stddef.h>  // size_t türü için eklenmiştir

// routes ve routeCount'u diğer dosyalarda kullanılabilir yapmak için extern anahtar kelimesi kullanıyoruz.
extern int routes[100];
extern int routeCount;

// Kullanıcı doğrulama işlevleri
int login(const char *username, const char *password);
void registerUser(const char *username, const char *password);

// Güzergah ve tarif yönetimi işlevleri
void loadSchedulesFromFile(const char *filename);
void showSchedules();
void calculateFare(const char *route, const char *ticketType);
void alertForDelays();

// Veri işleme algoritmaları
void compressAndSaveData(const char *data);
char *decompressData();
void addRoute(int routeID);
void removeRoute(int routeID);
void searchText(const char *text, const char *pattern);

// Dosya saklama ve geri çağırma
void insertFileIndex(int key);
void removeFileIndex(int key);
int searchFileIndex(int key);

// Güçlü bağlantılı bileşenleri bulma işlevi
void findStronglyConnectedComponents();

// Ağ keşfi için BFS/DFS algoritmaları
void exploreUsingBFS(int start);
void exploreUsingDFS(int start);

// Double Linked List Yapısı ve İşlevleri
typedef struct DoubleNode {
  int data;
  struct DoubleNode *next;
  struct DoubleNode *prev;
} DoubleNode;

DoubleNode *createDoubleNode(int data);
void insertDoubleNode(DoubleNode **head, int data);
void deleteDoubleNode(DoubleNode **head, int data);
void printDoubleList(DoubleNode *head);

// XOR Linked List Yapısı ve İşlevleri
typedef struct XORNode {
  int data;
  struct XORNode *npx; // XOR of next and previous node
} XORNode;

XORNode *createXORNode(int data);
void insertXORNode(XORNode **head, int data);
void deleteXORNode(XORNode **head, int data);
void printXORList(XORNode *head);
XORNode *XOR(XORNode *a, XORNode *b);  // XOR işlevi prototipi eklendi

// Sparse Matrix Yapısı ve İşlevleri
typedef struct SparseMatrixNode {
  int row;
  int col;
  int value;
  struct SparseMatrixNode *next;
} SparseMatrixNode;

SparseMatrixNode *createSparseNode(int row, int col, int value);
void insertSparseNode(SparseMatrixNode **head, int row, int col, int value);
int getSparseValue(SparseMatrixNode *head, int row, int col);
void printSparseMatrix(SparseMatrixNode *head);

#endif // PUBLICTRANSPORTATIONSCHEDULER_H
