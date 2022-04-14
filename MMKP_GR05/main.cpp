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

  instance_name = instance;

  int timelimit = atoi(stimelimit);

  std::cout << "Instance name: " << instance << "\n";
  std::cout << "Timelimit: " << timelimit << "s\n";

  signal(SIGINT, signalHandler);

  ReaderWriter readerWriter;
  KnapsackHandler sack_handler = readerWriter.read_instance(instance);

  mid = clock();
  
  printf("time reading file: %.8fs \n", ((float)mid - start)/CLOCKS_PER_SEC);

  //compute greedy
  GreedyAlgo greedy(sack_handler.get_class_handler().get_number_of_pockets(), 0.61);
  sack_handler.set_remaining_sack(greedy.compute_greedy(sack_handler));

  //compute local search
  LocalSearch local_search(greedy.get_final_sequence(), -1);
  sack_handler.set_remaining_sack(local_search.compute_local_search(sack_handler));
  // std::vector<int> res = local_search.compute_local_search(sack_handler);
  
  std::vector<int> prev_local_sol = local_search.get_final_solution();
  std::vector<int> res;

  for(int i = 0; i < 3; i++){
    LocalSearch local_search2(prev_local_sol, 3);

    res = local_search2.compute_local_search(sack_handler);

    sack_handler.set_remaining_sack(res);

    prev_local_sol = local_search2.get_final_solution();
  }

  end = clock();

  final_sequence = prev_local_sol;
  // final_sequence = greedy.get_final_sequence();
  // std::vector<int> res = sack_handler.get_remaining_sack();
  
  printf("time: %.8fs \n", ((float)end - start)/CLOCKS_PER_SEC);

  //code to check pocket sizes and the value
  int final_value = 0;
  ClassHandler class_handler = sack_handler.get_class_handler();

  for (int i = 0; i < sack_handler.get_class_handler().get_number_of_classes(); i++)
  {
    ClassInstance class_instance = class_handler.get_instance_at(i);

    ClassRow class_row = class_instance.get_rows()[final_sequence[i]];

    final_value += class_row.get_value();
  }

  std::cout << "Final value: " << final_value << "\n";

  std::cout << "Remaining pocket size:" << "\n";

  for (int size : res)
  {
    std::cout << size << " ";
  }
  
  std::cout << "\n";

  signalHandler(0);

  return 0;
}

/*g++ main.cpp ClassHandler.cpp ClassHandler.h ClassInstance.h ClassInstance.cpp
 * ClassRow.cpp ClassRow.h ReaderWriter.h ReaderWriter.cpp GreedyAlgo.h
 * GreedyAlgo.cpp */