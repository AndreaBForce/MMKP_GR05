#include "GreedyAlgo.h"
#include <iostream>
void GreedyAlgo::compute_greedy(ClassHandler class_handler) {
  for (int i = 0; i < class_handler.get_number_of_classes(); i++) {
    add_value(
        best_of_instance(class_handler.get_instance_at(i), class_handler.get_number_of_pockets()));
  }
}

int GreedyAlgo::best_of_instance(ClassInstance class_instance, int pockets) {
  float min = 99999, average = 0;
  int index = 0, current = 0;

  for (ClassRow row : class_instance.getRows()) {

    for (int valore : row.getRighe()) {
      average += valore;
    }

    // Cosi tengo conto anche del valore e vedo di massimizzarlo in qualche modo
    average = (average / row.get_row_values().size()) / row.get_value();

    if (average <= min) {
      min = average;
      index = current;
    }

    current++;
  }
  // std::cout << index << std::endl;

  return index;
};