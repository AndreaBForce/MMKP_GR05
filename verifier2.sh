#!/bin/bash

for file in Instances/standard/mmkp_a_07.txt;
do
  ./mmkp_verifier -i "$file" -t 60 -s result.csv -g MMKP_GR05;
done