#ifndef CLASSROW_H
#define CLASSROW_H

#include <vector>
/*Classe che definisce la singola row della classe instanza*/
class ClassRow {
public:
  void push_row_value(int value) { this->row_values.push_back(value); };
  void set_value(int value) { this->value = value; };
  int get_value() { return this->value; };
  std::vector<int> get_row_values() { return this->row_values; };

private:
  int value;
  std::vector<int> row_values;
};

#endif // CLASSROW