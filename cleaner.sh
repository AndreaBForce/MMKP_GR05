#!/bin/bash

for file in Instances/standard/*.out;
do
  rm -f "$file";
done

for file in Instances/standard/*.time;
do
  rm -f "$file";
done

for file in Instances/large/*.out;
do
  rm -f "$file";
done

for file in Instances/large/*.time;
do
  rm -f "$file";
done