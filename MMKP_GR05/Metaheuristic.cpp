#include "Metaheuristic.h"
#include <iostream>
#include <stdbool.h>
#include <algorithm>
#include <math.h>

std::vector<int> Metaheuristic::compute_metaheuristic(KnapsackHandler sack_handler){
    ClassHandler class_handler = sack_handler.get_class_handler();
    std::vector<int> res = sack_handler.get_remaining_sack();
    std::vector<ClassInstance> class_list = class_handler.get_class_list();
    int best_score = 0;

    for(int z = 0; z<iterations; z++){

        for (int i = 0; i < class_handler.get_number_of_classes(); i++) {
            ClassInstance class_instance = class_list[i];
            std::vector<ClassRow> class_rows = class_instance.get_rows();
            std::vector<ClassRow> class_rows_cp = class_instance.get_rows();
            int init_index = initial_solution[class_instance.get_id()];
            
            //sort class rows by value
            std::sort(class_rows.begin(), class_rows.end(), 
                    [](ClassRow &c1, ClassRow &c2) -> bool
                    {
                        return c1.get_value() < c2.get_value();
                    });

            int sorted_index = get_sorted_index(class_rows, init_index);

            int num_of_steps = class_rows.size() - sorted_index;

            //search for a better solution, if no one is found the actual index is kept
            int impv_index = init_index;
            for(int k=0; k < num_of_steps; k++){
                int impv_sol = improve_solution(class_rows, sorted_index, res, class_rows_cp[impv_index]);

                if (impv_sol == -1)
                {
                    metaheuristic_sol[class_instance.get_id()] = impv_index;
                    break;
                }else{
                    metaheuristic_sol[class_instance.get_id()] = impv_sol;
                    impv_index = impv_sol;
                }
                
                sorted_index++;
            }

            //if no better solution is found we try to worsen the actual
            int worse_index = init_index;
            if (init_index == impv_index)
            {
                //if the index is not the first (=0) we search for a worse solution
                sorted_index = get_sorted_index(class_rows, init_index);
                int m_val = sorted_index;

                for(int j=0; j<m_val; j++){

                    if(sorted_index > 0){
                        worse_index = worsen_solution(class_rows, sorted_index, res, class_rows_cp[init_index]);
                    }else{
                        break;
                    }

                    if(worse_index != init_index){
                        break;
                    }

                    sorted_index--;
                }
            }

            //compute probabilita: if it's good we keep the new index
            if(init_index != worse_index){
                double r = ((double) rand() / (RAND_MAX));
                ClassRow old_row = class_rows_cp[init_index];
                ClassRow worse_row = class_rows_cp[worse_index];
                double prob = exp(-(old_row.get_value() - worse_row.get_value())/probability);

                if(prob > r){
                    metaheuristic_sol[class_instance.get_id()] = worse_index;
                }

                //we keep the remaining resources updated
                std::vector<int> val_to_remove = class_rows_cp[metaheuristic_sol[class_instance.get_id()]].get_row_values();
                for (int j = 0; j < res.size(); j++)
                {
                    res[j] -= val_to_remove[j];
                }
            }
        }

        //we compute the total value of the solution and we compare this with the best score that we found before
        int result = 0;
        for(int i = 0; i < class_handler.get_number_of_classes(); i++){
            ClassInstance class_instance = class_list[i];
            int row_val = class_instance.get_rows()[metaheuristic_sol[i]].get_value();

            result += row_val;
        }

        if(result > best_score){
            best_score = result;
            meta_best_sol = metaheuristic_sol;
        }

        //reduction of the C parameter (referred to the paramenter used for computing the probability in the Simulated Annealing algorithm)
        if( z%how_often == 0){
            probability -= 1;
            if (probability == 0){
                probability = 1;
            }
        }
        
        //we keep the solution updated
        initial_solution = metaheuristic_sol;
    }
    return res;
}

int Metaheuristic::worsen_solution(std::vector<ClassRow> &class_rows, int sorted_index, std::vector<int> &res, ClassRow old_row){
    std::vector<int> old_row_values = old_row.get_row_values();

    int worse_idx = sorted_index - 1;

    ClassRow new_row = class_rows[worse_idx];
    std::vector<int> new_row_values = new_row.get_row_values();
    
    //reset values
    for (int j = 0; j < res.size(); j++)
    {
        res[j] += old_row_values[j];
    }

    //check new values
    if (!is_sack_full(res, new_row_values))
    {
        return new_row.get_id();
    }else{
        for (int j = 0; j < res.size(); j++)
        {
            res[j] -= old_row_values[j];
        }
        return old_row.get_id();
    }
}

int Metaheuristic::improve_solution(std::vector<ClassRow> &class_rows, int sorted_index, std::vector<int> &res, ClassRow old_row){
    std::vector<int> old_row_values = old_row.get_row_values();

    int first_improv = sorted_index < (class_rows.size()-1) ? sorted_index + 1 : -1;
    if (first_improv == -1)
    {
        return -1;
    }

    ClassRow new_row = class_rows[first_improv];
    std::vector<int> new_row_values = new_row.get_row_values();
    
    //reset values
    for (int j = 0; j < res.size(); j++)
    {
        res[j] += old_row_values[j];
    }

    //check new values
    if (!is_sack_full(res, new_row_values))
    {
        for (int j = 0; j < res.size(); j++)
        {
            res[j] -= new_row_values[j];
        }
        return new_row.get_id();
    }else{
        for (int j = 0; j < res.size(); j++)
        {
            res[j] -= old_row_values[j];
        }
        return old_row.get_id();
    }
}


int Metaheuristic::get_sorted_index(std::vector<ClassRow> &v, int init_index){
    for (int j = 0; j < v.size(); j++)
    {
        if (v[j].get_id() == init_index)
        {
            return j;
        }
    }
    return -1;
}

bool Metaheuristic::is_sack_full(std::vector<int> &v, std::vector<int> &row_values){
    for (int i = 0; i < v.size(); i++)
    {
        if ((v[i]-row_values[i]) < 0)
        {
            return true;
        }
    }
    return false;
}
