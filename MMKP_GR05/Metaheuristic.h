#ifndef METAHEURISTIC_H
#define METAHEURISTIC_H
#include <vector>
#include "KnapsackHandler.h"

class Metaheuristic{
public:
    Metaheuristic(std::vector<int> initial_solution, int probability, int iterations, int how_often){
        this->initial_solution = initial_solution;
        metaheuristic_sol = std::vector<int>(initial_solution.size(), 0);
        meta_best_sol = std::vector<int>(initial_solution.size(), 0);
        this->probability = probability;
        this->iterations = iterations;
        this->how_often = how_often;
    };
    ~Metaheuristic(){};

    std::vector<int> compute_metaheuristic(KnapsackHandler sack_handler);

    std::vector<int> get_final_solution(){return meta_best_sol;};

private:
    int probability;
    int iterations;
    int how_often;
    std::vector<int> initial_solution;
    std::vector<int> metaheuristic_sol;
    std::vector<int> meta_best_sol;

    int get_sorted_index(std::vector<ClassRow> &v, int old_index);
    bool is_sack_full(std::vector<int> &v, std::vector<int> &row_values);
    int improve_solution(std::vector<ClassRow> &class_rows, int sorted_index, std::vector<int> &res, ClassRow old_row);
    int worsen_solution(std::vector<ClassRow> &class_rows, int sorted_index, std::vector<int> &res, ClassRow old_row);
};


#endif