#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H
#include <vector>
#include "KnapsackHandler.h"

class LocalSearch{
public:
    LocalSearch(std::vector<int> initial_solution, int step_num){
        this->initial_solution = initial_solution;
        local_search_sol = std::vector<int>(initial_solution.size(), 0);
        this->step_num = step_num;
    };
    ~LocalSearch(){};

    std::vector<int> compute_local_search(KnapsackHandler sack_handler);

    std::vector<int> get_final_solution(){return local_search_sol;};


private:
    int step_num;
    std::vector<int> initial_solution;
    std::vector<int> local_search_sol;

    int partition(std::vector<ClassRow> &v, int begin, int end);
    void quicksort(std::vector<ClassRow> &v, int begin, int end);
    std::vector<int> get_local_serch_sol(){return local_search_sol;};
    void swap(std::vector<ClassRow> &v, int x, int y);
    int get_sorted_index(std::vector<ClassRow> &v, int old_index);
    bool is_sack_full(std::vector<int> &v, std::vector<int> &row_values);
    int improve_solution(std::vector<ClassRow> &class_rows, int sorted_index, std::vector<int> &res, ClassRow old_row);
};


#endif