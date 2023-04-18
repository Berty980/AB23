#!/bin/bash
g++ main.cpp -o cifrar_y_descifrar -std=c++11
g++ test_cases_generator.cpp -o test_cases_generator -std=c++11

./test_cases_generator 10 messages/message10.txt
./test_cases_generator 100 messages/message100.txt
./test_cases_generator 1000 messages/message1000.txt
./test_cases_generator 10000 messages/message10000.txt
./test_cases_generator 100000 messages/message100000.txt

echo Cifrado y descifrado con mensaje de 10 caracteres
./cifrar_y_descifrar keys/key1.txt messages/message10.txt decrytions/out.txt
echo ""

echo Cifrado y descifrado con mensaje de 100 caracteres
./cifrar_y_descifrar keys/key1.txt messages/message100.txt decrytions/out.txt
echo ""

echo Cifrado y descifrado con mensaje de 1000 caracteres
./cifrar_y_descifrar keys/key1.txt messages/message1000.txt decrytions/out.txt
echo ""

echo Cifrado y descifrado con mensaje de 10000 caracteres
./cifrar_y_descifrar keys/key1.txt messages/message10000.txt decrytions/out.txt
echo ""

echo Cifrado y descifrado con mensaje de 100000 caracteres
./cifrar_y_descifrar keys/key1.txt messages/message100000.txt decrytions/out.txt
echo ""

echo Cifrado y descifrado con clave erronea
./cifrar_y_descifrar keys/wrongKey.txt messages/message100000.txt decrytions/out.txt
echo ""
