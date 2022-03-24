# MMKP_GR05
Risolutore per multiple-choice multidimensional knapsack problem

Obbiettivo di risolvere il problema:
Leggere il file e ottimizzare la soluzione
Scegliere un item per classe e ottenere il VALUE massimo

Esempio di Instanza letta:
//700 numero totale di classi
//25 numero totale di sacche interne
700 25
//3500 ecc (potrebbe essere diverso) indica la capacita di ogni tasca dello zaino
3500 3500 3500 3500 3500 3500 3500 3500 3500 3500 3500 3500 3500 3500 3500 3500 3500 3500 3500 3500 3500 3500 3500 3500 3500
//10 indica il numero di item per classe
10
//646 - 685 è il VALUE di ogni oggetto
646 2 7 7 1 5 4 2 4 7 5 1 6 2 3 8 4 8 1 8 2 2 2 6 2 8
685 7 1 1 5 10 7 2 9 10 1 1 1 1 9 5 7 5 3 2 6 5 10 2 10 6
722 9 10 7 2 2 6 10 8 4 1 9 10 3 8 1 3 8 2 7 8 3 8 3 4 9
...
...

File di output:
N interi partendo da 0


-Per il momento la greedy, va bene cosi poi modificheremo i robi