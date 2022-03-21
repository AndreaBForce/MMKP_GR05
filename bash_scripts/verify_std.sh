#!/bin/bash
for i in $(ls -d MMKP_GR*);
do
  cd ${i};
  echo "Verifying for group " ${i};
  for full_name in $(ls ./mmkp_*.txt);
  do
    ../mmkp_verify -i ${full_name} -t 60 -s ../stat_file.csv -g ${i}
  done
  cd ..;
done