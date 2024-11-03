#ifndef PUBLICTRANSPORTATIONSCHEDULER_H
#define PUBLICTRANSPORTATIONSCHEDULER_H

// Kullanıcı doğrulama işlevleri
int login(const char *username, const char *password);
void registerUser(const char *username, const char *password);

// Güzergah ve tarif yönetimi işlevleri
void loadSchedulesFromFile(const char *filename);
void showSchedules();
void calculateFare(const char *route, const char *ticketType);
void alertForDelays();

// Veri işleme algoritmaları
void compressAndSaveData(const char *data); // Huffman Kodlaması için placeholder
char *decompressData();                      // Huffman Kodlaması için placeholder
void addRoute(int routeID);                  // Çift yönlü bağlı liste işlevi
void removeRoute(int routeID);
void searchText(const char *text, const char *pattern); // KMP Algoritması için placeholder

// Dosya saklama ve geri çağırma (B+ Ağaç yapısı yerine basit işlevler)
void insertFileIndex(int key);
void removeFileIndex(int key);
int searchFileIndex(int key);

// Güçlü bağlantılı bileşenleri bulma işlevi
void findStronglyConnectedComponents();

// Ağ keşfi için BFS/DFS algoritmaları
void exploreUsingBFS(int start);
void exploreUsingDFS(int start);

#endif // PUBLICTRANSPORTATIONSCHEDULER_H
