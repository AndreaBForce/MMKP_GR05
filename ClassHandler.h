#ifndef CLASSHANDLER_H
#define CLASSHANDLER_H

#include "ClassInstance.h"
#include <vector>

/*Classe che con una lista di instanze di classi gestisce esse*/
class ClassHandler {
public:
  ClassHandler() {}
  ~ClassHandler() {}

  void setNumberOfClasses(int numberOfClasses) {
    this->numberOfClasses = numberOfClasses;
  };
  void setNumberOfPockets(int numberOfPockets) {
    this->numberOfPockets = numberOfPockets;
  };
  void setPocketCapacity(int pocketCapacity) {
    this->pocketCapacity = pocketCapacity;
  };

  int getNumberOfPockets() { return this->numberOfPockets; };
  int getNumberOfClasses() { return this->numberOfClasses; };

  void initZaino(int capacita) { this->zaino.push_back(capacita); };
  void addClassInstance(ClassInstance classe) {
    this->classi.push_back(classe);
  };

  ClassInstance getInstanceAt(int index) { return classi.at(index); };

  void print();

private:
  int numberOfClasses;
  int numberOfPockets;
  int pocketCapacity;

  std::vector<ClassInstance> classi;

  // Instanziare vector di pockets che è il nostro zaino
  std::vector<int> zaino;
};

#endif // CLASSHANDLER