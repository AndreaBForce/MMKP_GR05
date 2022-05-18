#include "GreedyAlgo.h"
#include "ReaderWriter.h"
#include "KnapsackHandler.h"
#include "LocalSearch.h"
#include "Metaheuristic.h"
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
  ClassHandler class_handler = sack_handler.get_class_handler();
  std::vector<ClassInstance> class_list = class_handler.get_class_list();

  //compute greedy
  GreedyAlgo greedy(class_handler.get_number_of_pockets(), 0.61);
  sack_handler.set_remaining_sack(greedy.compute_greedy(sack_handler));

  std::vector<int> greedy_sol = greedy.get_final_sequence();

  //compute local search
  LocalSearch local_search(greedy_sol, -1);
  std::vector<int> local_remaining = local_search.compute_local_search(sack_handler);
  sack_handler.set_remaining_sack(local_remaining);
  
  std::vector<int> local_sol = local_search.get_final_solution();

  //backup solution
  final_sequence = local_sol;

  //compute metaheuristic
  if(timelimit == 1){
    int p1,p2,p3;
    
    if(class_handler.get_number_of_classes() >= 700){
      p1 = 45;
      p2 = 215;
      p3 = 5;
    }else{
      p1 = 47;
      p2 = 225;
      p3 = 5;
    }
    Metaheuristic m_heu_fast(local_sol, p1, p2, p3);
    sack_handler.set_remaining_sack(m_heu_fast.compute_metaheuristic(sack_handler));

    final_sequence = m_heu_fast.get_final_solution();
  }else{
    
    Metaheuristic m_heu2(local_sol, 47, 225, 5);
    sack_handler.set_remaining_sack(m_heu2.compute_metaheuristic(sack_handler));
    
    std::vector<int> sol2 = m_heu2.get_final_solution();
    int result2 = 0;
    for(int i = 0; i < class_handler.get_number_of_classes(); i++){
        ClassInstance class_instance = class_list[i];
        int row_val = class_instance.get_rows()[sol2[i]].get_value();

        result2 += row_val;
    }

    Metaheuristic m_heu(local_sol, 100, 490, 5);
    sack_handler.set_remaining_sack(local_remaining);
    sack_handler.set_remaining_sack(m_heu.compute_metaheuristic(sack_handler));

    std::vector<int> sol1 = m_heu.get_final_solution();
    
    int result = 0;
    for(int i = 0; i < class_handler.get_number_of_classes(); i++){
        ClassInstance class_instance = class_list[i];
        int row_val = class_instance.get_rows()[sol1[i]].get_value();

        result += row_val;
    }

    if (result2 > result)
    {
      final_sequence = sol2;
    }else{
      final_sequence = sol1;
    }
  }
  
  signalHandler(0);

  return 0;
}

/*g++ main.cpp ClassHandler.cpp ClassHandler.h ClassInstance.h ClassInstance.cpp
 * ClassRow.cpp ClassRow.h ReaderWriter.h ReaderWriter.cpp GreedyAlgo.h
 * GreedyAlgo.cpp */