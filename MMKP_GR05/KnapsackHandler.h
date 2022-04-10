#ifndef KNAPSACKHANDLER_H
#define KNAPSACKHANDLER_H

#include <vector>
#include "ClassHandler.h"

class KnapsackHandler
{
private:
    /* data */
    std::vector<int> sack;
    std::vector<int> remaining_sack;
    ClassHandler class_handler;

public:
    KnapsackHandler(int num_pockets){
        sack.reserve(num_pockets);
    }
    ~KnapsackHandler() {}

    std::vector<int> get_sack(){return sack;};

    std::vector<int> get_remaining_sack(){return remaining_sack;};

    void set_remaining_sack(std::vector<int> v){ remaining_sack = v;};

    void add_pocket_size(int capacity) { sack.push_back(capacity);};

    void substract_pocket_size(int value, int index){ sack[index] = sack[index] - value;};

    ClassHandler get_class_handler(){return class_handler;};

    void set_class_handler(ClassHandler class_handler){ this->class_handler = class_handler; };
};

#endif