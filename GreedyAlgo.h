#ifndef GREEDY_H
#define GREEDY_H
#include "ClassHandler.h"
#include "KnapsackHandler.h"
#include <vector>
class GreedyAlgo {
public:
  void compute_greedy(KnapsackHandler sack_handler);
  int best_of_instance(ClassInstance class_instance, int pockets);
  void add_value(int value) { this->sequence.push_back(value); };
  std::vector<int> get_final_sequence() { return this->sequence; };

private:
  std::vector<int> sequence;
};

#endif // GREEDY