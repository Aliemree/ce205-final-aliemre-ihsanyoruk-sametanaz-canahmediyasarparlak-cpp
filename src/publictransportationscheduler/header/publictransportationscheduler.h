#ifndef PUBLICTRANSPORTATIONSCHEDULER_H
#define PUBLICTRANSPORTATIONSCHEDULER_H

#include <string>
#include <unordered_map>
#include <stack>
#include <queue>
#include <vector>

namespace Coruh {
namespace PublicTransportationScheduler {

class PublicTransportationScheduler {
 public:
  // User Authentication
  bool login(const std::string &username, const std::string &password);
  void registerUser(const std::string &username, const std::string &password);

  // Schedule and Route Management
  void loadSchedulesFromFile(const std::string &filename);
  void showSchedules();
  void calculateFare(const std::string &route, const std::string &ticketType);
  void alertForDelays();

  // Algorithms for data handling
  void compressAndSaveData(const std::string &data); // Huffman Coding
  std::string decompressData();
  void addRoute(int routeID);    // Double Linked List
  void removeRoute(int routeID);
  void searchText(const std::string &text, const std::string &pattern); // KMP Algorithm

  // File storage and retrieval using a B+ Tree structure
  void insertFileIndex(int key);
  void removeFileIndex(int key);
  int searchFileIndex(int key);

  // Strongly Connected Components
  void findStronglyConnectedComponents();

  // BFS/DFS for network exploration
  void exploreUsingBFS(int start);
  void exploreUsingDFS(int start);

 private:
  std::unordered_map<std::string, std::string> userDatabase;
  std::vector<int> routes;
  std::stack<std::string> historyStack;
  std::priority_queue<int> priorityQueue;
};

} // namespace PublicTransportationScheduler
} // namespace Coruh

#endif // PUBLICTRANSPORTATIONSCHEDULER_H
