#!/bin/bash

for file in mmkp_d*;
do
  ./mmkp -i "$file" -t 60;
done