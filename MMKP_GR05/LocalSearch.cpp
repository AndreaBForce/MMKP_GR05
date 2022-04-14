#include "LocalSearch.h"
#include <iostream>
#include <stdbool.h>
#include <algorithm>

std::vector<int> LocalSearch::compute_local_search(KnapsackHandler sack_handler){
    std::cout << "works" << std::endl;
    ClassHandler class_handler = sack_handler.get_class_handler();
    std::vector<int> res = sack_handler.get_remaining_sack();
    std::vector<ClassInstance> class_list = class_handler.get_class_list();

    std::cout << class_list[0].get_class_size() << "\n";

    for (int i = 0; i < class_handler.get_number_of_classes(); i++) {
        ClassInstance class_instance = class_list[i];
        std::vector<ClassRow> class_rows = class_instance.get_rows();
        std::vector<ClassRow> class_rows_cp = class_instance.get_rows();
        int old_index = initial_solution[class_instance.get_id()];
        
        //sort class rows by value
        std::sort(class_rows.begin(), class_rows.end(), 
                [](ClassRow &c1, ClassRow &c2) -> bool
                {
                    return c1.get_value() < c2.get_value();
                });

        int sorted_index = get_sorted_index(class_rows, old_index);

        int num_of_steps = class_rows.size() - sorted_index;

        for(int k=0; k < num_of_steps; k++){
            int impv_sol = improve_solution(class_rows, sorted_index, res, class_rows_cp[old_index]);

            if (impv_sol == -1)
            {
                local_search_sol[class_instance.get_id()] = old_index;
                break;
            }else{
                local_search_sol[class_instance.get_id()] = impv_sol;
                old_index = impv_sol;
            }
            
            sorted_index++;
        }                
    }
    return res;
}

int LocalSearch::improve_solution(std::vector<ClassRow> &class_rows, int sorted_index, std::vector<int> &res, ClassRow old_row){
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

int LocalSearch::get_sorted_index(std::vector<ClassRow> &v, int old_index){
    for (int j = 0; j < v.size(); j++)
    {
        if (v[j].get_id() == old_index)
        {
            return j;
        }
    }
    return -1;
}

bool LocalSearch::is_sack_full(std::vector<int> &v, std::vector<int> &row_values){
    for (int i = 0; i < v.size(); i++)
    {
        if ((v[i]-row_values[i]) < 0)
        {
            return true;
        }
    }
    return false;
}