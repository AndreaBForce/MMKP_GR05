#!/bin/bash

cd MMKP_GR05;

g++ -O3 -o ../mmkp -I . *.cpp -lm;