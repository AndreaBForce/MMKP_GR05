#ifndef CLASSINSTANCE_H
#define CLASSINSTANCE_H

#include "ClassRow.h"
#include <vector>

/*Classe che gestisce la singola instanza della class_row W1 che contiene la
 * singola row*/
class ClassInstance {
public:
  ClassInstance(int num_rows, int id){
    this->id = id;
    rows.reserve(num_rows);
  }
  ~ClassInstance(){}
  
  void push_row(ClassRow class_row) { this->rows.push_back(class_row); };
  std::vector<ClassRow> get_rows() { return this->rows; };
  int get_id(){return id;};

private:
  int id;

  std::vector<ClassRow> rows;
};

#endif // CLASSINSTANCE