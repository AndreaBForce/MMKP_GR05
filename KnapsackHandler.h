#ifndef KNAPSACKHANDLER_H
#define KNAPSACKHANDLER_H

#include <vector>
#include "ClassHandler.h"

class KnapsackHandler
{
private:
    /* data */
    std::vector<int> sack;
    ClassHandler class_handler;

public:
    KnapsackHandler(/* args */);
    ~KnapsackHandler();

    std::vector<int> get_sack(){return sack;};

    void add_pocket_size(int capacity) { sack.push_back(capacity);};

    void substract_pocket_size(int value, int index){ sack[index] = sack[index] - value;};

    ClassHandler get_class_handler(){return class_handler;};

    void set_class_handler(ClassHandler class_handler){ this->class_handler = class_handler; };
};

#endif