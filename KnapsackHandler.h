#ifndef KNAPSACKHANDLER_H
#define KNAPSACKHANDLER_H

#include <vector>

class KnapsackHandler
{
private:
    /* data */
    std::vector<int> sack;

public:
    KnapsackHandler(/* args */);
    ~KnapsackHandler();

    std::vector<int> get_sack(){return sack;};

    void add_pocket_size(int capacity) { sack.push_back(capacity);};
};

#endif