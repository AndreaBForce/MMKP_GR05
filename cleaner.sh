#!/bin/bash

for file in Instances/standard/*.out;
do
  rm "$file";
done

for file in Instances/standard/*.time;
do
  rm "$file";
done