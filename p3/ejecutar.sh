#!/bin/bash
g++ main.cpp -o main -std=c++11

./main -i ./pruebas/diccionario_3906.txt -o ./resultados/resultados_3906_p_2.txt -p 1
./main -i ./pruebas/diccionario_3906.txt -o ./resultados/resultados_3906_p_10.txt -p 10
./main -i ./pruebas/diccionario_3906.txt -o ./resultados/resultados_3906_p_20.txt -p 20

./main -i ./pruebas/diccionario_100.txt -o ./resultados/resultados_100_l_10.txt -l 10
./main -i ./pruebas/diccionario_250.txt -o ./resultados/resultados_250_l_10.txt -l 10
./main -i ./pruebas/diccionario_625.txt -o ./resultados/resultados_625_l_10.txt -l 10
./main -i ./pruebas/diccionario_1562.txt -o ./resultados/resultados_1562_l_10.txt -l 10
./main -i ./pruebas/diccionario_3906.txt -o ./resultados/resultados_3906_l_10.txt -l 10

./main -i ./pruebas/diccionario_100.txt -o ./resultados/resultados_100_p_10.txt -p 10
./main -i ./pruebas/diccionario_250.txt -o ./resultados/resultados_250_p_10.txt -p 10
./main -i ./pruebas/diccionario_625.txt -o ./resultados/resultados_625_p_10.txt -p 10
./main -i ./pruebas/diccionario_1562.txt -o ./resultados/resultados_1562_p_10.txt -p 10
./main -i ./pruebas/diccionario_3906.txt -o ./resultados/resultados_3906_p_10.txt -p 10

./main -i ./pruebas/diccionario_100.txt -o ./resultados/resultados_100.txt
./main -i ./pruebas/diccionario_250.txt -o ./resultados/resultados_250.txt
./main -i ./pruebas/diccionario_625.txt -o ./resultados/resultados_625.txt
./main -i ./pruebas/diccionario_1562.txt -o ./resultados/resultados_1562.txt
./main -i ./pruebas/diccionario_3906.txt -o ./resultados/resultados_3906.txt
