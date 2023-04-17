#!/bin/bash
g++ test_cases_generator.cpp -o gen
./gen 100 pruebas/diccionario_100.txt
./gen 300 pruebas/diccionario_300.txt
./gen 800 pruebas/diccionario_900.txt
./gen 2700 pruebas/diccionario_2700.txt
./gen 8100 pruebas/diccionario_8100.txt
