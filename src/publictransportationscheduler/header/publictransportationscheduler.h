#ifndef PUBLICTRANSPORTATIONSCHEDULER_H
#define PUBLICTRANSPORTATIONSCHEDULER_H

#include <string>

namespace Coruh {
namespace PublicTransportationScheduler {
class PublicTransportationScheduler {
 public:
  static void loadSchedulesFromFile(const std::string &filename);
  static void showSchedules();
  static void calculateFare(const std::string &route, const std::string &ticketType);
  static void alertForDelays();

  static bool login(const std::string &username, const std::string &password);
  static void registerUser(const std::string &username, const std::string &password);
};
}
}

#endif // PUBLICTRANSPORTATIONSCHEDULER_H
