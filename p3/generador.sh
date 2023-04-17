#!/bin/bash
g++ test_cases_generator.cpp -o gen
./gen 100 pruebas/diccionario_100.txt
./gen 1000 pruebas/diccionario_1000.txt
./gen 5000 pruebas/diccionario_5000.txt
