#include "KnapsackHandler.h"

std::vector<int> KnapsackHandler::subtract_best_from_sack(ClassInstance class_instance,int index,std::vector<int> pockets){

    int i = 0;
    for(int space_occupied : class_instance.get_rows().at(index).get_row_values()){
        pockets[i] -= space_occupied;
        i++; 
    }
    return pockets;
}