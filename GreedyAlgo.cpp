#include "GreedyAlgo.h"
#include <iostream>
void GreedyAlgo::computeGreedy(ClassHandler classe) {
  for (int i = 0; i < classe.getNumberOfClasses(); i++) {
    addValue(
        bestOfInstance(classe.getInstanceAt(i), classe.getNumberOfPockets()));
  }
}

int GreedyAlgo::bestOfInstance(ClassInstance instanza, int pockets) {
  float min = 99999, average = 0;
  int index = 0, current = 0;

  for (ClassRow row : instanza.getRows()) {
    for (int valore : row.getRighe()) {
      average += valore;
    }
    average = average / row.getRighe().size();

    if (average <= min) {
      min = average;
      index = current;
    }

    current++;
  }
  // std::cout << index << std::endl;
  return index;
};