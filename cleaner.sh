#!/bin/bash

for file in test_files/*.out;
do
  rm "$file";
done

for file in test_files/*.time;
do
  rm "$file";
done