#include "GreedyAlgo.h"
#include "ReaderWriter.h"
#include "KnapsackHandler.h"
#include "LocalSearch.h"
#include <csignal>
#include <cstring>
#include <iostream>
#include <string>
#include <chrono>

std::vector<int> final_sequence;
std::string instance_name;

char *getOption(int argc, char *argv[], const char *option) {
  for (int i = 0; i < argc; ++i)
    if (strcmp(argv[i], option) == 0)
      return argv[i + 1];
  return NULL;
}

void signalHandler( int signum ) {
  ReaderWriter writer;
  writer.save_vector_to_file(final_sequence, instance_name);
  exit(signum);  
}

int main(int argc, char *argv[]) {
  
  char *instance = getOption(argc, argv, std::string("-i").c_str());
  char *stimelimit = getOption(argc, argv, std::string("-t").c_str());
  if (instance == NULL || stimelimit == NULL) {
    std::cout << "Parametri inseriti non correttamente\n";
    std::cout << "Parametri corretti: -t tempo -i datoproblema" << std::endl;
    std::cout << "Esempio: -t 60 -i instance" << std::endl;
    exit(1);
  }

  instance_name = instance;

  int timelimit = atoi(stimelimit);

  signal(SIGINT, signalHandler);

  ReaderWriter readerWriter;
  KnapsackHandler sack_handler = readerWriter.read_instance(instance);

  //compute greedy
  GreedyAlgo greedy(sack_handler.get_class_handler().get_number_of_pockets(), 0.61);
  sack_handler.set_remaining_sack(greedy.compute_greedy(sack_handler));

  //compute local search
  LocalSearch local_search(greedy.get_final_sequence(), -1);
  sack_handler.set_remaining_sack(local_search.compute_local_search(sack_handler));
  
  std::vector<int> prev_local_sol = local_search.get_final_solution();
  std::vector<int> res;

  for(int i = 0; i < 3; i++){
    LocalSearch local_search2(prev_local_sol, 3);

    res = local_search2.compute_local_search(sack_handler);

    sack_handler.set_remaining_sack(res);

    prev_local_sol = local_search2.get_final_solution();
  }

  final_sequence = prev_local_sol;
  
  signalHandler(0);

  return 0;
}

/*g++ main.cpp ClassHandler.cpp ClassHandler.h ClassInstance.h ClassInstance.cpp
 * ClassRow.cpp ClassRow.h ReaderWriter.h ReaderWriter.cpp GreedyAlgo.h
 * GreedyAlgo.cpp */