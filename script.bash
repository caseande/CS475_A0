#!/bin/bash



#number of threads:
for t in 1 4
do
    for s in 10 100 1000 10000 100000
    do
        g++ -DNUMT=$t -DNUMTRIES=$s 0.cpp -o omptest -lm -fopenmp
        ./omptest
    done
done
