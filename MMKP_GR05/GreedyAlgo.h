#ifndef GREEDY_H
#define GREEDY_H
#include "ClassHandler.h"
#include "KnapsackHandler.h"
#include <vector>

//Classe che definisce l'algoritmo greedy
class GreedyAlgo {
public:
  GreedyAlgo(int num_classes, float tune_value){
    this->tune_value = tune_value;
    this->sequence.reserve(num_classes);
    pocket_weight = std::vector<int>(num_classes, 1);
  };

  ~GreedyAlgo(){};

  std::vector<int> compute_greedy(KnapsackHandler sack_handler);
  int best_of_instance(std::vector<ClassRow> rows, std::vector<int> pocket_sizes);
  void add_value(int value) { this->sequence.push_back(value); };
  std::vector<int> get_final_sequence() { return this->sequence; };

private:
  std::vector<int> substract_best_from_pockets(std::vector<int> row_values, std::vector<int> pockets, std::vector<int> initial_pockets);
  
  std::vector<int> sequence;
  std::vector<int> pocket_weight;

  //valori di tuning del greedy
  float tune_value;
};

#endif // GREEDY