#!/bin/bash
g++ main_branch_and_bound.cpp -o main_branch_and_bound
g++ main_brute_force.cpp -o main_brute_force
g++ test_generator.cpp -o test_generator

#./test_generator 3
#./main_brute_force pruebas.txt resultados_brute_force.txt
./main_branch_and_bound pruebas.txt resultados.txt