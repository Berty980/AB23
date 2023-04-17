#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

vector<vector<string>> separarPalabras(string s, set<string>& dic) {
    //matriz de programación dinámica que guarda las soluciones
    //de los subproblemas de tamaño 0 a n. Es por lo tanto un
    //vector unidimensional de soluciones (las soluciones son
    //particiones, es decir, vectores de vectores de palabras)
    vector<vector<vector<string>>> solutions(s.length() + 1);

    //rellenamos la matriz con el caso base para calcular el
    //subproblema más pequeño en base a este
    solutions[0] = {{}};

    //rellenamos la matriz
    for (int i = 1; i <= s.length(); i++) {
        for (int j = 0; j < i; j++) {
            //Si no hay soluciones para el subproblema tamaño j no
            //podemos construir una solución al subproblema tamaño i
            if (!solutions[j].empty()){
                string suffix = s.substr(j, i - j);
                //si el sufijo constituye una palabra añadimos la
                //partición a la solución de tamaño i
                if (dic.find(suffix) != dic.end()) {
                    for (vector<string> partition : solutions[j]) {
                        vector<string> partition_aux = partition;
                        partition_aux.push_back(suffix);
                        solutions[i].push_back(partition_aux);
                    }
                }
            }
        }
    }
    /*cout << "s.length() " << s.length() << endl;
    for (int i = 0; i <= s.length(); i++) {
        cout << "i = " << i << endl;
        for (int j = 0; j < solutions[i].size(); j++) {
            cout << "\t";
            for (int k = 0; k < solutions[i][j].size(); k++) {
                cout << solutions[i][j][k] << " ";
            }
            cout << endl;
        }
    }*/
    return solutions[s.length()];
}

void getSelections(set<string> dictionary, int selSize, string& sel, string& mod_sel) {
    int numWords = dictionary.size(); // Número de palabras en el dicionario
    string selection = "";  // Selección vacía
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, numWords-1);
    // Iterar hasta tener el número de palabras deseado en la selección
    while (selection.size() < selSize) {
        int idx = distrib(gen); // Obtenemos aleatorimente el índice de una palabra del diccionario
        auto it = dictionary.begin();
        advance(it, idx);
        // Añadimos la palabra a la selección
        selection += *it;
    }
    // Guardamos la selección en el parámetro de salida
    sel = selection;

    int LF = selection.size(); // Longitud de la selección (string)
    uniform_int_distribution<> distribModif(1, LF*10);
    // Recorremos cada carácter de la selección
    for (int i = 0; i < LF; i++) {
        // Obtenemos aleatoriamente la probabilidad de modificar el carácter
        int num = distribModif(gen);
        // Si la probabilidad es menor que 1 se modifica por otro carácter aleatorio
        if (num <= 1) {
            char newWord = 'a' + (rand() % 26);
            selection[i] = newWord;
        }
    }
    // Guardamos la selección modificada en otro parámetro de salida
    mod_sel = selection;
}

int main(int argc, char* argv[]) {
    if (argc < 1)
        cout << "Uso: main <diccionario> <resultados>" << endl
            << "\tdiccionario: nombre del fichero que contiene el diccionario" << endl
            << "\tdiccionario: nombre del fichero de salida (las posibles particiones solo se escriben en él)" << endl;


    auto maxReps = 100;

    ifstream dic(argv[1]);
    ofstream resultados(argv[2]);

    if (!dic) { // Verificar si se ha abierto el archivo correctamente
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    set<string> dictionary; // Diccionario de palabras
    string word;
    int a = 0;
    while (dic >> word)
        dictionary.insert(word);

    dic.close(); // Cerrar el archivo

    auto t_sel = chrono::nanoseconds(0);
    auto t_search = chrono::nanoseconds(0);
    std::vector<std::vector<std::string>> partitions;
    std::vector<std::vector<std::string>> partitions_mod;

    string sel, mod_sel;
    for (int i = 0; i < maxReps; i++) {
        sel = "", mod_sel = "";
        auto t0 = chrono::high_resolution_clock::now();
        getSelections(dictionary, dictionary.size() / 10, sel, mod_sel);
        auto t1 = chrono::high_resolution_clock::now();
        t_sel += chrono::duration_cast<chrono::nanoseconds>(t1 - t0);
    }
    for (int i = 0; i < maxReps; i++) {
        auto t0 = chrono::high_resolution_clock::now();
        partitions = separarPalabras(sel, dictionary);
        partitions_mod = separarPalabras(mod_sel, dictionary);
        auto t1 = chrono::high_resolution_clock::now();
        t_search += chrono::duration_cast<chrono::nanoseconds>(t1 - t0);
    }


    resultados << "Diccionario con " << dictionary.size() << " palabras" << endl;
    resultados << "\tTiempo de generación de las selecciones: " << t_sel.count()/maxReps * 1e-6 << " us " << endl;
    resultados << "\tTiempo de separación de palabras: " << t_search.count()/maxReps * 1e-6 << " us " << endl;
    resultados << "\tCadena: " << sel << endl << endl;
    cout << "Diccionario con " << dictionary.size() << " palabras" << endl;
    cout << "\tTiempo de generación de las selecciones: " << t_sel.count()/maxReps * 1e-6 << " us " << endl;
    cout << "\tTiempo de separación de palabras: " << t_search.count()/maxReps * 1e-6 << " us " << endl;


    if (partitions.empty()) {
        resultados << "\tLa cadena no es divisible" << endl;
    } else {
        resultados << "\t" << partitions.size() << " particiones posibles:" << endl;
        cout << "\t" << partitions.size() << " particiones posibles:" << endl;
        auto i = 0;
        for (auto& partition : partitions) {
            resultados << "\t\t";
            for (auto i = 0; i < partition.size(); i++) {
                resultados << partition[i];
                if (i < partition.size() - 1) {
                    resultados << " ";
                }
                i++;
            }
            resultados << endl;
        }
    }

    return 0;
}
