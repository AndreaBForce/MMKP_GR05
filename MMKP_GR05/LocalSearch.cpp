#include "LocalSearch.h"
#include <iostream>
#include <stdbool.h>

std::vector<int> LocalSearch::compute_local_search(KnapsackHandler sack_handler){
    std::cout << "works" << std::endl;
    ClassHandler class_handler = sack_handler.get_class_handler();
    std::vector<int> pockets = sack_handler.get_sack();
    std::vector<int> initial_pockets = sack_handler.get_sack();
    std::vector<int> res = sack_handler.get_remaining_sack();

    for (int i = 0; i < class_handler.get_number_of_classes(); i++) {
        ClassInstance class_instance = class_handler.get_instance_at(i);
        std::vector<ClassRow> class_rows = class_instance.get_rows();
        int old_index = initial_solution[i];
        
        //sort class rows by value   
        quicksort(class_rows, 0, class_rows.size()-1);
        int sorted_index = get_sorted_index(class_rows, old_index);
        int first_improv = sorted_index<class_rows.size()-1? sorted_index + 1 : -1;
        if (first_improv == -1)
        {
            /* code */
            local_search_sol[i] = old_index;
            continue;
        }
        
        ClassRow old_class = class_rows[sorted_index];
        ClassRow new_class = class_rows[first_improv];
        //reset values
        for (int j = 0; j < res.size(); j++)
        {
            res[j] += old_class.get_row_values()[j];
            // std::cout << res[j] << "\n";
        }

        //check new values
        if (!is_sack_full(res, new_class.get_row_values()))
        {
            for (int j = 0; j < res.size(); j++)
            {
                res[j] -= new_class.get_row_values()[j];
                // std::cout << res[j] << "\n";
            }
            local_search_sol[i] = new_class.get_id();
        }else{
            local_search_sol[i] = old_index;
        }
            
    }
    
    return res;
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

bool LocalSearch::is_sack_full(std::vector<int> v, std::vector<int> row_values){
    for (int i = 0; i < v.size(); i++)
    {
        if ((v[i]-row_values[i]) < 0)
        {
            return true;
        }
        
    }
    return false;
}