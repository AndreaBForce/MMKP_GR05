#ifndef CLASSROW_H
#define CLASSROW_H

#include <vector>
/*Classe che definisce la singola row della classe instanza*/
class ClassRow {
public:
  void pushRowValue(int value) { this->righe.push_back(value); };
  void setValue(int value) { this->value = value; };
  int getValue() { return this->value; };
  std::vector<int> getRighe() { return this->righe; };

private:
  int value;
  std::vector<int> righe;
};

#endif // CLASSROW