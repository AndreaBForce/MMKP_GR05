#!/bin/bash

# List all groups folders
for i in $(ls -d MMKP_GR*);
do
  echo "Running for group " ${i};
  cd ${i};
  for full_name in $(ls ../Instances/standard/mmkp_*.txt);
  do
    instance=$(basename ${full_name})
    # Copy instance file
    cp ${full_name} ${instance}

    # Run algorithm with timeout and store user time
    /usr/bin/time -f "%e" timeout -s 2 60s ./mmkp -i ${instance} -t 60 2>${instance}.time

    # Create out_standard folder if it does not exist
    mkdir -p out_standard;

    # Backup output and time files
    cp ${instance}.out out_standard;
    cp ${instance}.time out_standard;
  done
  cd ..;
done