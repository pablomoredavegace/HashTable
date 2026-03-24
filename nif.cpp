#include "nif.h"

#include <ctime>
#include <iomanip>


nif::nif() {
  static bool seeded = false;
  if (!seeded) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
  }

  Valor = std::rand() % 100000000;
}

nif::nif(long value) {
  if (value < 0) {
    value = -value;
  }
  Valor = value % 100000000;
}

nif::operator long() const {
  return Valor;
}

bool nif::operator==(const nif& other) const {
  return Valor==other.Valor;
}

bool nif::operator!=(const nif& other) const {
  return Valor!=other.Valor;
}

bool nif::operator<(const nif& other) const {
  return Valor < other.Valor;
}

bool nif::operator<=(const nif& other) const {
  return Valor <= other.Valor;
}

bool nif::operator>=(const nif& other) const {
  return Valor >= other.Valor;
}

std::ostream& operator<<(std::ostream& os, const nif& value) {
  os << std::setw(8) << std::setfill('0') << static_cast<long>(value);
  return os;
}