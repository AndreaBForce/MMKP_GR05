#!/bin/bash

for file in Instances/large/mmkp_*;
do
  ./mmkp -i "$file" -t 60;
done