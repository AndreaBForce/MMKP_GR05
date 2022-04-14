#!/bin/bash

for file in Instances/standard/mmkp_*;
do
  ./mmkp -i "$file" -t 60;
done