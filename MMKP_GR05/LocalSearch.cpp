#include "LocalSearch.h"
#include <iostream>
#include <stdbool.h>



std::vector<int> LocalSearch::compute_local_search(KnapsackHandler sack_handler){
    std::cout << "works" << std::endl;
    ClassHandler class_handler = sack_handler.get_class_handler();
    std::vector<int> res = sack_handler.get_remaining_sack();

    for (int i = 0; i < class_handler.get_number_of_classes(); i++) {
        ClassInstance class_instance = class_handler.get_instance_at(i);
        std::vector<ClassRow> class_rows = class_instance.get_rows();
        std::vector<ClassRow> class_rows_cp = class_instance.get_rows();
        int old_index = initial_solution[i];

        //sort class rows by value   
        quicksort(class_rows, 0, class_rows.size()-1);
        int sorted_index = get_sorted_index(class_rows, old_index);

        int row_id = sorted_index;
        int impv_sol = 0;
        for(int k=0; k < step_num; k++){
            impv_sol = improve_solution(class_rows, sorted_index, res);

            if (impv_sol == -1)
            {
                local_search_sol[i] = old_index;
                break;
            }else{
                local_search_sol[i] = impv_sol;
                // old_index = impv_sol;
                // std::cout << row_id << " ";
            }
            
            std::cout << sorted_index << " ";
            // sorted_index++;
            // std::cout << "\n"; 
            
        }    
        std::cout << "\n"; 
            
    }
    return res;
}

int LocalSearch::improve_solution(std::vector<ClassRow> &class_rows, int sorted_index, std::vector<int> &res){
    ClassRow old_row = class_rows[sorted_index];
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

int LocalSearch::partition(std::vector<ClassRow> &v, int begin, int end){
    int pivot = end;
	int j = begin;
	for(int i=begin; i<end; i++){
		
        if(v[i].get_value() < v[pivot].get_value()){
			swap(v, i, j);
			j++;
		}
	}
	swap(v, j, pivot);
	return j;
}
void LocalSearch::quicksort(std::vector<ClassRow> &v, int begin, int end){
    if (begin<end){
        int p = partition(v, begin, end);
        quicksort(v, begin, p-1);
        quicksort(v, p+1, end);
    }
}

void LocalSearch::swap(std::vector<ClassRow> &v, int x, int y){
    ClassRow tmp = v[x];
    v[x] = v[y];
    v[y] = tmp;
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