#!/bin/bash

./compile_mmkp.sh

#./mmkp -i instances/large/mmkp_d_256.txt -t 60
./mmkp -i instances/standard/mmkp_c_23.txt -t 60
./mmkp -i instances/standard/mmkp_c_24.txt -t 60
./mmkp -i instances/standard/mmkp_b_02.txt -t 60
#./mmkp -i instances/standard/mmkp_d_100.txt -t 60