#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {

    //Comprobar el número de parámetros
    if (argc < 3) {
        cerr << "Uso: test_cases_generator n out_file" << endl;
        return 1;
    }

    // Primer parámetro: tamaño del diccionario
    int n = atoi(argv[1]);
    // Segundo parámetro: nombre del fichero de salida
    ofstream f_out(argv[2]);
    set<string> dictionary;
    //Generar diccionario
    mt19937 mt(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> dist(97, 122);
    while(dictionary.size() < n){
        uniform_int_distribution<int> wordLength(2, 10);
        string word = "";
        for(int j = 0; j < wordLength(mt); j++){
            int ascii = dist(mt);
            char _char = static_cast<char>(ascii);
            word += _char;
        }
        if(dictionary.find(word) == dictionary.end()) {
            f_out << word << " ";
            dictionary.insert(word);
        }
    }

    //Escribir mensaje
    f_out.close();

    return 0;
}