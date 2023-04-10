#!/bin/bash



#number of threads:
for t in 1 4
do
    for s in 20 #10 100 1000 10000 100000
    do
        # g++ -DNUMT=$t -DNUMTRIES=$s 0.cpp -o omptest -lm -fopenmp
        clang -DNUMT=$t -DNUMTRIES=$s -Xclang -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include -lomp 0_1.cpp -o omptest
        ./omptest
    done
done
