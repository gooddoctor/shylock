#include "engine.h"

std::ostream& engine::operator<< (std::ostream& os, const String& obj) {
  os << obj.mb_str();
  return os;
}



