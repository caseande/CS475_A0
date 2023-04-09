#!/bin/bash

#number of threads:
for t in 1 4
do
    g++ -DNUMT=$t 0.cpp -o omptest -lm -fopenmp
    ./omptest
done
