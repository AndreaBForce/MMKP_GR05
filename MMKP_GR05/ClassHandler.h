#ifndef CLASSHANDLER_H
#define CLASSHANDLER_H

#include "ClassInstance.h"
#include <vector>

/*Classe che con una lista di instanze di classi gestisce esse*/
class ClassHandler {
public:
  ClassHandler() {}
  ClassHandler(int num_of_classes) { 
    this->number_of_classes = num_of_classes;
    class_list.reserve(num_of_classes);
  }
  ~ClassHandler() {}

  void set_number_of_classes(int numberOfClasses) {
    this->number_of_classes = numberOfClasses;
  };
  void set_number_of_pockets(int numberOfPockets) {
    this->number_of_pockets = numberOfPockets;
  };
  void set_pocket_capacity(int pocketCapacity) {
    this->pocket_capacity = pocketCapacity;
  };

  int get_number_of_pockets() { return this->number_of_pockets; };
  int get_number_of_classes() { return this->number_of_classes; };

  void add_class_instance(ClassInstance class_instance) {
    this->class_list.push_back(class_instance);
  };

  ClassInstance get_instance_at(int index) { return class_list[index]; };

  std::vector<ClassInstance> get_class_list(){return class_list;};

  void print();

private:
  int number_of_classes;
  int number_of_pockets;
  int pocket_capacity;

  std::vector<ClassInstance> class_list;
};

#endif // CLASSHANDLER