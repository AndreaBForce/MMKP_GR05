#include "GreedyAlgo.h"
#include "ReaderWriter.h"
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

int main(int argc, char *argv[]) {
  clock_t start, end;
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

  std::cout << "Instance name: " << instance << "\n";
  std::cout << "Timelimit: " << timelimit << "s\n";

  ReaderWriter readerWriter;
  KnapsackHandler sack_handler = readerWriter.read_instance(instance);

  //prima leggo il file così inizializzo l'algoritmo con il numero di indici di output da avere
  GreedyAlgo greedy;
  greedy.compute_greedy(sack_handler);

  readerWriter.save_vector_to_file(greedy.get_final_sequence());
  
  end = clock();
  printf("time: %.8fs \n", ((float)end - start)/CLOCKS_PER_SEC);

  return 0;
}

/*g++ main.cpp ClassHandler.cpp ClassHandler.h ClassInstance.h ClassInstance.cpp
 * ClassRow.cpp ClassRow.h ReaderWriter.h ReaderWriter.cpp GreedyAlgo.h
 * GreedyAlgo.cpp */