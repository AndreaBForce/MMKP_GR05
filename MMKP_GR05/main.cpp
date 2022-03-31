#include "GreedyAlgo.h"
#include "ReaderWriter.h"
#include "KnapsackHandler.h"
#include <csignal>
#include <cstring>
#include <iostream>
#include <string>
#include <chrono>

char *getOption(int argc, char *argv[], const char *option) {
  for (int i = 0; i < argc; ++i)
    if (strcmp(argv[i], option) == 0)
      return argv[i + 1];
  return NULL;
}

void signalHandler( int signum ) {
   std::cout << "Interrupt signal (" << signum << ") received.\n";

   exit(signum);  
}

// TODO REMOVE before assignment
// method that checks all tune values between 0 and 1 with 1ms granularity
void check_tune_values(KnapsackHandler sack_handler){
  std::vector<float> tune_values;
  float delta = 0.001;

  for (int i = 0; i < 1000; i++)
  {
    //prima leggo il file così inizializzo l'algoritmo con il numero di indici di output da avere
    GreedyAlgo greedy(sack_handler.get_class_handler().get_number_of_pockets(), delta*i);
    std::vector<int> res = greedy.compute_greedy(sack_handler);

    int err = 0;
    for (int size : res){
      if (size < 0)
      {
        err = 1;
        break;
      }
    }
    if (err == 0)
    {
      tune_values.push_back(i*delta);
    }
    
  }

  std::cout << "Tune values" << "\n";
  for (float v : tune_values)
  {
    std::cout << v << " ";
  }
  std::cout << "\n";
}

int main(int argc, char *argv[]) {
  clock_t start, mid, end;
  start = clock();
  
  char *instance = getOption(argc, argv, std::string("-i").c_str());
  char *stimelimit = getOption(argc, argv, std::string("-t").c_str());
  if (instance == NULL || stimelimit == NULL) {
    std::cout << "Parametri inseriti non correttamente\n";
    std::cout << "Parametri corretti: -t tempo -i datoproblema" << std::endl;
    std::cout << "Esempio: -t 60 -i instance" << std::endl;
    exit(1);
  }

  int timelimit = atoi(stimelimit);

  // std::cout << "Instance name: " << instance << "\n";
  // std::cout << "Timelimit: " << timelimit << "s\n";

  signal(SIGINT, signalHandler);

  ReaderWriter readerWriter;
  KnapsackHandler sack_handler = readerWriter.read_instance(instance);

  mid = clock();
  
  // printf("time reading file: %.8fs \n", ((float)mid - start)/CLOCKS_PER_SEC);

  //prima leggo il file così inizializzo l'algoritmo con il numero di indici di output da avere
  GreedyAlgo greedy(sack_handler.get_class_handler().get_number_of_pockets(), 0.61);
  std::vector<int> res = greedy.compute_greedy(sack_handler);
  
  end = clock();

  readerWriter.save_vector_to_file(greedy.get_final_sequence(), instance, ((float)end - start)/CLOCKS_PER_SEC);
  
  // printf("time: %.8fs \n", ((float)end - start)/CLOCKS_PER_SEC);

  //code to check pocket sizes and the value
  int final_value = 0;
  ClassHandler class_handler = sack_handler.get_class_handler();
  std::vector<int> final_sequence = greedy.get_final_sequence();
  for (int i = 0; i < sack_handler.get_class_handler().get_number_of_classes(); i++)
  {
    /* code */
    ClassInstance class_instance = class_handler.get_instance_at(i);

    ClassRow class_row = class_instance.get_rows()[final_sequence[i]];
    std::vector<int> row_values = class_row.get_row_values(); 

    final_value += class_row.get_value();
    // for (int j = 0; j < class_handler.get_number_of_pockets(); j++)
    // {
    //   /* code */
    //   sack_handler.substract_pocket_size(row_values[j], j);
    // }
  }

  std::cout << "Final value: " << final_value << "\n";

  std::cout << "Remaining pocket size:" << "\n";

  for (int size : res)
  {
    std::cout << size << " ";
  }
  
  std::cout << "\n";


  return 0;
}

/*g++ main.cpp ClassHandler.cpp ClassHandler.h ClassInstance.h ClassInstance.cpp
 * ClassRow.cpp ClassRow.h ReaderWriter.h ReaderWriter.cpp GreedyAlgo.h
 * GreedyAlgo.cpp */