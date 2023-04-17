#!/bin/bash
g++ main.cpp -o main
./main -i pruebas/diccionario_100.txt -o resultados/resultados_100.txt -l 100
./main -i pruebas/diccionario_250.txt -o resultados/resultados_250.txt -l 100
./main -i pruebas/diccionario_625.txt -o resultados/resultados_625.txt -l 100
./main -i pruebas/diccionario_1562.txt -o resultados/resultados_1562.txt -l 100
./main -i pruebas/diccionario_3906.txt -o resultados/resultados_3906.txt -l 100

./main -i pruebas/diccionario_100.txt -o resultados/resultados_100.txt -p 10
./main -i pruebas/diccionario_250.txt -o resultados/resultados_250.txt -p 10
./main -i pruebas/diccionario_625.txt -o resultados/resultados_625.txt -p 10
./main -i pruebas/diccionario_1562.txt -o resultados/resultados_1562.txt -p 10
./main -i pruebas/diccionario_3906.txt -o resultados/resultados_3906.txt -p 10

./main -i pruebas/diccionario_1562.txt -o resultados/resultados_1562.txt -p 2
./main -i pruebas/diccionario_1562.txt -o resultados/resultados_1562.txt -p 20
