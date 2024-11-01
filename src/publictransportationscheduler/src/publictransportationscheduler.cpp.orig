#include "publictransportationscheduler.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

namespace Coruh {
namespace PublicTransportationScheduler {

static std::unordered_map<std::string, std::string> userDatabase;

void PublicTransportationScheduler::loadSchedulesFromFile(const std::string &filename) {
  std::ifstream file(filename);

  if (!file) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  std::cout << "Schedules loaded from file: " << filename << std::endl;
}

void PublicTransportationScheduler::showSchedules() {
  std::cout << "Displaying bus and train schedules..." << std::endl;
}

void PublicTransportationScheduler::calculateFare(const std::string &route, const std::string &ticketType) {
  double baseFare = 5.0;  // Örnek baz ücret

  if (ticketType == "Student") {
    baseFare *= 0.5;  // Öğrenci indirimi
  }

  std::cout << "Calculated fare for " << route << " with " << ticketType << " ticket: " << baseFare << std::endl;
}

void PublicTransportationScheduler::alertForDelays() {
  std::cout << "No delays currently reported." << std::endl;
}

bool PublicTransportationScheduler::login(const std::string &username, const std::string &password) {
  if (userDatabase.find(username) != userDatabase.end() && userDatabase[username] == password) {
    std::cout << "Login successful." << std::endl;
    return true;
  }

  std::cout << "Invalid username or password." << std::endl;
  return false;
}

void PublicTransportationScheduler::registerUser(const std::string &username, const std::string &password) {
  if (userDatabase.find(username) == userDatabase.end()) {
    userDatabase[username] = password;
    std::cout << "User registered successfully." << std::endl;
  } else {
    std::cout << "Username already exists." << std::endl;
  }
}
}
}
