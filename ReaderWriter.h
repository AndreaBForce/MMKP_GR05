#ifndef READERWRITER_H
#define READERWRITER_H
#include "ClassHandler.h"
class ReaderWriter {
public:
  ClassHandler readInstance(char *instanceName);
  void printInstance();

  void saveVectorToFile(std::vector<int> vettore);

private:
};

#endif // READERWRITER