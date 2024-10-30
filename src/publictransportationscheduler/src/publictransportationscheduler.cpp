#include "publictransportationscheduler.h"
#include <stdexcept>

namespace Coruh {
namespace PublicTransportationScheduler {

double PublicTransportationScheduler::add(double a, double b) {
  return a + b;
}

double PublicTransportationScheduler::subtract(double a, double b) {
  return a - b;
}

double PublicTransportationScheduler::multiply(double a, double b) {
  return a * b;
}

double PublicTransportationScheduler::divide(double a, double b) {
  if (b == 0) {
    throw std::invalid_argument("Division by zero is not allowed.");
  }

  return a / b;
}
}
}
