#!/bin/bash

for file in test_files/mmkp_d*;
do
  ./mmkp -i "$file" -t 60;
done