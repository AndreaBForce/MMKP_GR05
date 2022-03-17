#include "ReaderWriter.h"
#include "KnapsackHandler.h"
#include "ClassHandler.h"
#include "ClassInstance.h"
#include "ClassRow.h"
#include <fstream>
#include <iostream>

ClassHandler ReaderWriter::read_instance(char *instance_name) {
  ClassHandler class_handler;
  KnapsackHandler sack_handler;

  // Leggi l'header del file (fino alla prima instanza)
  std::fstream my_file;
  my_file.open(instance_name, std::ios::in);

  int ch;

  // Lettura header del file
  // Setto numero classi
  my_file >> ch;
  class_handler.set_number_of_classes(ch);

  // Setto numero pockets
  my_file >> ch;
  class_handler.set_number_of_pockets(ch);

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
    // Todo aggiungere un id
    // Dimensione instanza classe (10 esempio mmkp_d_244.txt)
    ClassInstance class_instance;
    my_file >> instance_dimension;

    // std::cout << instance_dimension << std::endl;
    // Su ogni instanza ciclo per leggere ogni riga di essa
    for (int i = 0; i < instance_dimension; i++) {
      ClassRow class_row;
      my_file >> rowValue;
      // std::cout << rowValue << std::endl;
      class_row.set_value(rowValue);
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

  return class_handler;
  // Metodo di test per vedere se salvava i valori
  // classHandler.print();
}

void ReaderWriter::save_vector_to_file(std::vector<int> out_vector) {
  std::ofstream myfile;
  myfile.open("output.txt");

  for (int valore : out_vector) {
    myfile << valore << " ";
  }
  myfile.close();
}