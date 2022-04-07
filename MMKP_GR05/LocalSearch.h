#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H
#include <vector>
#include "KnapsackHandler.h"

class LocalSearch{
public:
    LocalSearch(std::vector<int> initial_solution, int step_num){
        this->initial_solution = initial_solution;
        local_search_sol.reserve(initial_solution.size());
        this->step_num = step_num;
    };
    ~LocalSearch(){};

    void compute_local_search(KnapsackHandler sack_handler);

    std::vector<int> get_final_solution(){return local_search_sol;};


private:
    int step_num;
    std::vector<int> initial_solution;
    std::vector<int> local_search_sol;
};


#endif