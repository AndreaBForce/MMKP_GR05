#include "ClassHandler.h"
#include "ClassInstance.h"
#include <iostream>

void ClassHandler::print() {
  for (ClassInstance classe : classi) {
    for (ClassRow row : classe.getRows()) {
      std::cout << row.getValue() << std::endl;
    }
  }
}