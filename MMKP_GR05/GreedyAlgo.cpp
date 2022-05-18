#include "GreedyAlgo.h"
#include <iostream>

std::vector<int> GreedyAlgo::compute_greedy(KnapsackHandler sack_handler) {
  ClassHandler class_handler = sack_handler.get_class_handler();
  std::vector<int> pockets = sack_handler.get_sack();
  std::vector<int> initial_pockets = sack_handler.get_sack();

  for (int i = 0; i < class_handler.get_number_of_classes(); i++) {
    ClassInstance class_instance = class_handler.get_instance_at(i);
    std::vector<ClassRow> class_rows = class_instance.get_rows();
    
    int index = best_of_instance( class_rows, pockets);

    pockets = substract_best_from_pockets(class_rows[index].get_row_values(), pockets, initial_pockets);

    add_value(index);

  }
  return pockets;
}

int GreedyAlgo::best_of_instance(std::vector<ClassRow> rows, std::vector<int> pocket_sizes) {
  float min = 99999;
  int index = 0, current = 0;
  
  for (ClassRow row : rows) {
    float average = 0;
    std::vector<int> row_values = row.get_row_values();

    for (int i = 0; i < pocket_sizes.size(); i++)
    {
      average += (float) row_values[i]/pocket_sizes[i]*pocket_weight[i];
    }

    if (average <= min) {
      min = average;
      index = current;
    }

    current++;
  }

  return index;
}

std::vector<int> GreedyAlgo::substract_best_from_pockets(std::vector<int> row_values, std::vector<int> pockets, std::vector<int> initial_pockets){

  for (int i = 0; i < row_values.size() ; i++)
  {
    pockets[i] -= row_values[i];
    if ( (float) pockets[i]/initial_pockets[i] <= tune_value)
    {
      pocket_weight[i]+= 2;
    }
  }
  
  return pockets;
}