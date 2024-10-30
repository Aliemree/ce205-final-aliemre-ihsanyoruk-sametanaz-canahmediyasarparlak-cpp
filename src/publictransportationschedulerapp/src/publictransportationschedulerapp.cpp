#include "publictransportationschedulerapp.h"
#include "publictransportationscheduler.h"
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace Coruh::PublicTransportationScheduler;

struct StopData {
  std::string stopName;
  int passengerCount; // Mevcut yolcu sayısı
};

// Örnek durak verileri
std::vector<StopData> stops = {
  {"Station A", 50},
  {"Station B", 70},
  {"Station C", 30},
  {"Station D", 90}
};

void showMenu() {
  std::cout << "\n=== Public Transportation Scheduler ===\n";
  std::cout << "1. View Stop Information\n";
  std::cout << "2. Estimate Passenger Count\n";
  std::cout << "3. Calculate Distance Between Stops\n";
  std::cout << "4. Perform Custom Calculation\n";
  std::cout << "0. Exit\n";
  std::cout << "Select an option: ";
}

void viewStopInformation() {
  std::cout << "\n=== Stop Information ===\n";

  for (const auto &stop : stops) {
    std::cout << "Stop: " << stop.stopName << " - Current Passengers: " << stop.passengerCount << "\n";
  }
}

void estimatePassengerCount() {
  int totalPassengers = 0;

  for (const auto &stop : stops) {
    totalPassengers += stop.passengerCount;
  }

  double average = static_cast<double>(totalPassengers) / stops.size();
  std::cout << "Estimated Total Passengers: " << totalPassengers << "\n";
  std::cout << "Average Passengers per Stop: " << average << "\n";
}

void calculateDistanceBetweenStops() {
  std::string stop1, stop2;
  std::cout << "Enter the first stop name: ";
  std::cin >> stop1;
  std::cout << "Enter the second stop name: ";
  std::cin >> stop2;
  // Örnek bir mesafe hesaplaması
  int distance = abs(static_cast<int>(stop1[0] - stop2[0])) * 5;
  std::cout << "Estimated Distance between " << stop1 << " and " << stop2 << " is: " << distance << " km.\n";
}

void performCustomCalculation() {
  double a, b, result;
  int operation;
  std::cout << "Enter first number: ";
  std::cin >> a;
  std::cout << "Enter second number: ";
  std::cin >> b;
  std::cout << "\nSelect Operation:\n";
  std::cout << "1. Add\n";
  std::cout << "2. Subtract\n";
  std::cout << "3. Multiply\n";
  std::cout << "4. Divide\n";
  std::cout << "Choice: ";
  std::cin >> operation;

  try {
    switch (operation) {
      case 1:
        result = PublicTransportationScheduler::add(a, b);
        break;

      case 2:
        result = PublicTransportationScheduler::subtract(a, b);
        break;

      case 3:
        result = PublicTransportationScheduler::multiply(a, b);
        break;

      case 4:
        result = PublicTransportationScheduler::divide(a, b);
        break;

      default:
        std::cout << "Invalid operation.\n";
        return;
    }

    std::cout << "Result: " << result << "\n";
  } catch (const std::invalid_argument &e) {
    std::cerr << "Error: " << e.what() << "\n";
  }
}

int main() {
  int choice;

  while (true) {
    showMenu();
    std::cin >> choice;

    switch (choice) {
      case 1:
        viewStopInformation();
        break;

      case 2:
        estimatePassengerCount();
        break;

      case 3:
        calculateDistanceBetweenStops();
        break;

      case 4:
        performCustomCalculation();
        break;

      case 0:
        std::cout << "Exiting the application.\n";
        return 0;

      default:
        std::cout << "Invalid choice. Please try again.\n";
        break;
    }
  }

  return 0;
}
