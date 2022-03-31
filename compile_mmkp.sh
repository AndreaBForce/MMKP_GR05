#!/bin/bash

cd MMKP_GR05;

g++ -O3 -std=c++17 -o ../mmkp -I . *.cpp -lm;