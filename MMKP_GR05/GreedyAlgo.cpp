#include "GreedyAlgo.h"
#include <iostream>

std::vector<int> GreedyAlgo::compute_greedy(KnapsackHandler sack_handler) {
  // float tuning = 0.0;
  ClassHandler class_handler = sack_handler.get_class_handler();
  std::vector<int> pockets = sack_handler.get_sack();
  std::vector<int> initial_pockets = sack_handler.get_sack();

  for (int i = 0; i < class_handler.get_number_of_classes(); i++) {
    ClassInstance class_instance = class_handler.get_instance_at(i);
    std::vector<ClassRow> class_rows = class_instance.get_rows();
    
    int index = best_of_instance( class_rows, pockets);

    pockets = substract_best_from_pockets(class_rows[index].get_row_values(), pockets, initial_pockets);

    add_value(index);

    // if (tuning >= this->tune_value)
    // {
    //   std::cout << "tune value: " << tuning << "\n";
    //   for (auto v : class_rows[index].get_row_values())
    //   {
    //     std::cout << v << " ";  
    //   }
    //   std::cout << "\n"; 
    //   for (auto p : pockets)
    //   {
    //     std::cout << p << " ";  
    //   }
    //   std::cout << "\n";  
    // }

    // tuning += this->tune_delta;  
  }
  // for (int value : pocket_weight) {
  //     std::cout << value << " ";
  //   }
  return pockets;
}

int GreedyAlgo::best_of_instance(std::vector<ClassRow> rows, std::vector<int> pocket_sizes) {
  float min = 99999;
  int index = 0, current = 0;
  
  for (ClassRow row : rows) {
    float average = 0;
    std::vector<int> row_values = row.get_row_values();
    // for (int value : row.get_row_values()) {
    //   average += value;
    // }

    for (int i = 0; i < pocket_sizes.size(); i++)
    {
      /* code */
      average += (float) row_values[i]/pocket_sizes[i]*pocket_weight[i];
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