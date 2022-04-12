#include "ReaderWriter.h"
#include "KnapsackHandler.h"
#include "ClassHandler.h"
#include "ClassInstance.h"
#include "ClassRow.h"
#include <fstream>
#include <iostream>

KnapsackHandler ReaderWriter::read_instance(char *instance_name) {
  // Leggi l'header del file (fino alla prima instanza)
  std::fstream my_file;
  my_file.open(instance_name, std::ios::in);

  int ch;

  // Lettura header del file
  // Setto numero classi
  my_file >> ch;
  //creo qua la classHandler e passo il numero di classi
  ClassHandler class_handler(ch);
  // class_handler.set_number_of_classes(ch);

  // Setto numero pockets
  my_file >> ch;
  int pockets = ch;
  //Creo qua il knapsack e passo il numero di tasche
  KnapsackHandler sack_handler(pockets);
  class_handler.set_number_of_pockets(pockets);

  // Inizializzo tasche zaino
  for (int i = 0; i < class_handler.get_number_of_pockets(); i++) {
    my_file >> ch;
    sack_handler.add_pocket_size(ch);
  }
  // Fine lettura header

  // Inizia la lettura dei dati
  int counter = 0, instance_dimension = 0, rowValue = 0;

  // Ciclo che va su tutte le classi
  for (int k = 0; k < class_handler.get_number_of_classes(); k++) {
    // Dimensione instanza classe (10 esempio mmkp_d_244.txt)
    my_file >> instance_dimension;
    ClassInstance class_instance(instance_dimension, k);
    //creo qui la classInstance e passo il numero di righe che ha

    // std::cout << instance_dimension << std::endl;
    // Su ogni instanza ciclo per leggere ogni riga di essa
    for (int i = 0; i < instance_dimension; i++) {
      //qua creo una righa, devo passare il numero di pockets
      my_file >> rowValue;
      ClassRow class_row(pockets, rowValue, i);
      // Su ogni row pusho i valori e li salvo

      for (int j = 0; j < class_handler.get_number_of_pockets(); j++) {
        my_file >> ch;
        class_row.push_row_value(ch);
      }
      // Aggiungo row e aggiungo la classInstance
      class_instance.push_row(class_row);
    }
    class_handler.add_class_instance(class_instance);
  }

  sack_handler.set_class_handler(class_handler);
  return sack_handler;
}

void ReaderWriter::save_vector_to_file(std::vector<int> out_vector, std::string instance_name) {
  std::ofstream out_file;
  std::ofstream time_file;
  out_file.open(instance_name + ".out");
  time_file.open(instance_name + ".time");

  for (int valore : out_vector) {
    out_file << valore << " ";
  }
  out_file.close();

  time_file << 0.1;
  time_file.close();
}