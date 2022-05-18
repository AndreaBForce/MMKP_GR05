#include "ReaderWriter.h"
#include "KnapsackHandler.h"
#include "ClassHandler.h"
#include "ClassInstance.h"
#include "ClassRow.h"
#include <fstream>
#include <iostream>

KnapsackHandler ReaderWriter::read_instance(char *instance_name) {
  // Read the header of the file (until the first instance)
  std::fstream my_file;
  my_file.open(instance_name, std::ios::in);

  int ch;

  // Set the number of classes
  my_file >> ch;
  
  ClassHandler class_handler(ch);

  // Set the number of pockets
  my_file >> ch;
  int pockets = ch;

  KnapsackHandler sack_handler(pockets);
  class_handler.set_number_of_pockets(pockets);

  // Init of knapsack pockets
  for (int i = 0; i < class_handler.get_number_of_pockets(); i++) {
    my_file >> ch;
    sack_handler.add_pocket_size(ch);
  }
  // end of the header

  // read of data
  int counter = 0, instance_size = 0, rowValue = 0;

  
  for (int k = 0; k < class_handler.get_number_of_classes(); k++) {
    // instance size
    my_file >> instance_size;

    ClassInstance class_instance(instance_size, k);

    // read of every row of the class
    for (int i = 0; i < instance_size; i++) {
      
      //save the row values
      my_file >> rowValue;
      ClassRow class_row(pockets, rowValue, i);

      for (int j = 0; j < class_handler.get_number_of_pockets(); j++) {
        my_file >> ch;
        class_row.push_row_value(ch);
      }
      // add row and classInstance
      class_instance.push_row(class_row);
    }
    class_handler.add_class_instance(class_instance);
  }

  sack_handler.set_class_handler(class_handler);
  return sack_handler;
}

void ReaderWriter::save_vector_to_file(std::vector<int> out_vector, std::string instance_name) {
  std::ofstream out_file;
  out_file.open(instance_name + ".out");

  for (int valore : out_vector) {
    out_file << valore << " ";
  }

  out_file.close();
}