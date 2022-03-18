#include "GreedyAlgo.h"
#include <iostream>

void GreedyAlgo::compute_greedy(KnapsackHandler sack_handler) {
  ClassHandler class_handler = sack_handler.get_class_handler();

  for (int i = 0; i < class_handler.get_number_of_classes(); i++) {
    ClassInstance class_instance = class_handler.get_instance_at(i);
    int index = best_of_instance( class_instance, sack_handler.get_sack());
    add_value(index);  
  }
}

int GreedyAlgo::best_of_instance(ClassInstance class_instance, std::vector<int> pocket_sizes) {
  float min = 99999;
  int index = 0, current = 0;

  for (ClassRow row : class_instance.get_rows()) {
    float average = 0;

    // for (int value : row.get_row_values()) {
    //   average += value;
    // }

    for (int i = 0; i < pocket_sizes.size(); i++)
    {
      /* code */
      average += (float) row.get_row_values()[i]/pocket_sizes[i]*1000;
    }

    // std::cout << average << "\n";
    

    // Cosi tengo conto anche del valore e vedo di massimizzarlo in qualche modo
    // average = average / row.get_value();
    // average = (average / row.get_row_values().size()) / row.get_value();

    if (average <= min) {
      min = average;
      index = current;
      // std::cout << min << "\n";
      // std::cout << index << "\n";
    }

    current++;
  }
  // std::cout << "*****************************************\n";
  // std::cout << index << " ";

  //qui posso diminuire la dimensione delle tasche del sack, così vediamo quanto è buono

  return index;
};