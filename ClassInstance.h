#ifndef CLASSINSTANCE_H
#define CLASSINSTANCE_H

#include "ClassRow.h"
#include <vector>

/*Classe che gestisce la singola instanza della classe W1 che contiene la
 * singola row*/
class ClassInstance {
public:
  void pushRow(ClassRow classe) { this->rows.push_back(classe); };
  std::vector<ClassRow> getRows() { return this->rows; };

private:
  // Campi da rimuovere volendo
  int id;
  int done;

  std::vector<ClassRow> rows;
};

#endif // CLASSINSTANCE