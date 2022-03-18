#ifndef READERWRITER_H
#define READERWRITER_H
#include "ClassHandler.h"
#include "KnapsackHandler.h"

class ReaderWriter {
public:
  KnapsackHandler read_instance(char *instance_name);

  void save_vector_to_file(std::vector<int> out_vector);

private:
};

#endif // READERWRITER