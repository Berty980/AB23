#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {

    //Comprobar el número de parámetros
    if (argc < 3) {
        cerr << "Uso: test_cases_generator n out_file" << endl;
        return 1;
    }

    //Parsear el tamaño del mensaje
    int n = atoi(argv[1]);
    //parsear el nombre del fichero de salida
    ofstream f_out(argv[2]);

    //Generar mensaje
    string message = "";
    mt19937 mt(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> dist(32, 126);  //distribucion uniforme de los caracteres escribibles
    for(int i = 0; i < n; i++){
        int ascii_code = dist(mt);
        char ascii_char = static_cast<char>(ascii_code);
        message += ascii_char;
    }

    //Escribir mensaje
    f_out << message;
    f_out.close();

    return 0;
}