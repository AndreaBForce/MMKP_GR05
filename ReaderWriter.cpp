#include "ReaderWriter.h"
#include "ClassHandler.h"
#include "ClassInstance.h"
#include "ClassRow.h"
#include <fstream>
#include <iostream>

ClassHandler ReaderWriter::readInstance(char *instanceName) {
  ClassHandler classHandler;

  // Leggi l'header del file (fino alla prima instanza)
  std::fstream my_file;
  my_file.open(instanceName, std::ios::in);

  int ch;

  // Lettura header del file
  // Setto numero classi
  my_file >> ch;
  classHandler.setNumberOfClasses(ch);

  // Setto numero pockets
  my_file >> ch;
  classHandler.setNumberOfPockets(ch);

  // Inizializzo tasche zaino
  for (int i = 0; i < classHandler.getNumberOfPockets(); i++) {
    my_file >> ch;
    classHandler.initZaino(ch);
  }
  // Fine lettura header

  // Inizia la lettura dei dati
  int counter = 0, instance_dimension = 0, rowValue = 0;

  // Ciclo che va su tutte le classi
  for (int k = 0; k < classHandler.getNumberOfClasses(); k++) {
    // Todo aggiungere un id
    // Dimensione instanza classe (10 esempio mmkp_d_244.txt)
    ClassInstance classInstance;
    my_file >> instance_dimension;

    // std::cout << instance_dimension << std::endl;
    // Su ogni instanza ciclo per leggere ogni riga di essa
    for (int i = 0; i < instance_dimension; i++) {
      ClassRow classRow;
      my_file >> rowValue;
      // std::cout << rowValue << std::endl;
      classRow.setValue(rowValue);
      // Su ogni row pusho i valori e li salvo

      for (int j = 0; j < classHandler.getNumberOfPockets(); j++) {
        my_file >> ch;
        classRow.pushRowValue(ch);
      }
      // Aggiungo row e aggiungo la classInstance
      classInstance.pushRow(classRow);
    }
    classHandler.addClassInstance(classInstance);
  }

  return classHandler;
  // Metodo di test per vedere se salvava i valori
  // classHandler.print();
}

void ReaderWriter::saveVectorToFile(std::vector<int> vettore) {
  std::ofstream myfile;
  myfile.open("output.txt");

  for (int valore : vettore) {
    myfile << valore << " ";
  }
  myfile.close();
}