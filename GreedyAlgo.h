#ifndef GREEDY_H
#define GREEDY_H
#include "ClassHandler.h"
#include <vector>
class GreedyAlgo {
public:
  void computeGreedy(ClassHandler classe);
  int bestOfInstance(ClassInstance instanza, int pockets);
  void addValue(int value) { this->sequence.push_back(value); };
  std::vector<int> getFinalSequence() { return this->sequence; };

private:
  std::vector<int> sequence;
};

#endif // GREEDY