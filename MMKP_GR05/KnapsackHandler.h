#ifndef KNAPSACKHANDLER_H
#define KNAPSACKHANDLER_H

#include <vector>
#include "ClassHandler.h"

/*
Classe che gestisce la sacca
Contiene anche la classe ClassHandler
*/
class KnapsackHandler
{
public:

    KnapsackHandler(int num_pockets){
        sack.reserve(num_pockets);
    }

    ~KnapsackHandler() {}

    //Ritorna il vettore con la capienza
    std::vector<int> get_sack(){return sack;};

    //Aggiunge la dimensione al gestore della sacca
    void add_pocket_size(int capacity) { sack.push_back(capacity);};

    //Sottrae dalla sacca un valore occupato
    void substract_pocket_size(int value, int index){ sack[index] = sack[index] - value;};

    ClassHandler get_class_handler(){return class_handler;};

    void set_class_handler(ClassHandler class_handler){ this->class_handler = class_handler; };

private:
    
    std::vector<int> sack;
    ClassHandler class_handler;
};

#endif