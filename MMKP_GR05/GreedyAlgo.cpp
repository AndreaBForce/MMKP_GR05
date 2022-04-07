#include "GreedyAlgo.h"
#include <iostream>
#include <cmath>

std::vector<int> GreedyAlgo::compute_greedy(KnapsackHandler sack_handler) {
  ClassHandler class_handler = sack_handler.get_class_handler();
  std::vector<int> initial_pockets = sack_handler.get_sack();
  std::vector<int> pockets = sack_handler.get_sack();

  for (int i = 0; i < class_handler.get_number_of_classes(); i++) {
    ClassInstance class_instance = class_handler.get_instance_at(i);
    std::vector<ClassRow> class_rows = class_instance.get_rows();
    
    int index = best_of_instance( class_rows, pockets);

    pockets = substract_best_from_pockets(class_rows[index].get_row_values(), pockets, initial_pockets);

    add_value(index);
  }
  // for (int value : pocket_weight) {
  //     std::cout << value << " ";
  //   }
  return pockets;
}

int GreedyAlgo::best_of_instance(std::vector<ClassRow> rows, std::vector<int> pocket_sizes) {
  float min = -1;
  int index = 0, current = 0;
  
  for (ClassRow row : rows) {
    float average = 0;
    long pockets_norm = 0;
    std::vector<int> row_values = row.get_row_values();

    for (int i = 0; i < pocket_sizes.size(); i++)
    {
      pockets_norm += pow(pocket_sizes[i], 2);
      // average += (float) row_values[i]/pocket_sizes[i]*pocket_weight[i];
      average += (float) pow(row_values[i], 2);
    }

    average = sqrt(average)/sqrt(pockets_norm);


    if(min == -1.0){
      min = average;
      index = current;
    }

    if (average <= min) {
      min = average;
      index = current;
      // std::cout << min << "\n";
      // std::cout << index << "\n";
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