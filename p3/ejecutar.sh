#!/bin/bash
g++ main.cpp -o main
./main pruebas/diccionario_100.txt resultados/resultados_100.txt
./main pruebas/diccionario_250.txt resultados/resultados_250.txt
./main pruebas/diccionario_625.txt resultados/resultados_625.txt
./main pruebas/diccionario_1562.txt resultados/resultados_1562.txt
./main pruebas/diccionario_3906.txt resultados/resultados_3906.txt
