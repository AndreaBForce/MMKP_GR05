#!/bin/bash

for file in Instances/standard/mmkp_*.txt;
do
  ./mmkp_verify -i "$file" -t 60 -s result.csv -g MMKP_GR05;
done