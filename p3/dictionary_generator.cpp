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
        cerr << "Uso: dictionary_generator n out_file" << endl;
        return 1;
    }

    // Primer parámetro: tamaño del diccionario
    int n = atoi(argv[1]);
    // Segundo parámetro: nombre del fichero de salida
    ofstream dic_file(argv[2]);
    
    set<string> dictionary;
    mt19937 mt(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> dist(97, 122);
    
    // Generar diccionario
    while(dictionary.size() < n){
        uniform_int_distribution<int> wordLength(2, 10); // Longitud aleatoria de la palabra a generar
        string word = "";
        // Añado carácteres aleatorios a la palabra
        for(int j = 0; j < wordLength(mt); j++){
            int ascii = dist(mt);
            char _char = static_cast<char>(ascii);
            word += _char;
        }
        // Si la palabra no está contenida en el diccionario la añado
        if(dictionary.find(word) == dictionary.end()) {
            dic_file << word << " ";
            dictionary.insert(word);
        }
    }

    // Cerrar el archivo
    dic_file.close();

    return 0;
}
