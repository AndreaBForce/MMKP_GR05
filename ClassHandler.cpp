#include "ClassHandler.h"
#include "ClassInstance.h"
#include <iostream>

void ClassHandler::print() {
  for (ClassInstance classe : class_list) {
    for (ClassRow row : classe.getRows()) {
      std::cout << row.get_value() << std::endl;
    }
  }
}