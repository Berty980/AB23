#!/bin/bash
g++ dictionary_generator.cpp -o gen -std=c++11
./gen 100 pruebas/diccionario_100.txt
./gen 250 pruebas/diccionario_250.txt
./gen 625 pruebas/diccionario_625.txt
./gen 1562 pruebas/diccionario_1562.txt
./gen 3906 pruebas/diccionario_3906.txt
