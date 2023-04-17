#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <random>

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

void getSelections(set<string> dictionary, string& sel, string& mod_sel) {
    int numWords = dictionary.size();
    int selSize = numWords / 10;
    string selection = "";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, numWords-1);
    while (selection.size() < selSize) {
        int idx = distrib(gen);
        auto it = dictionary.begin();
        advance(it, idx);
        selection += *it;
    }
    sel = selection;

    int LF = selection.size();
    uniform_int_distribution<> distribModif(1, LF*10);
    for (int i = 0; i < LF; i++) {
        int num = distribModif(gen);
        if (num <= 1) {
            char newWord = 'a' + (rand() % 26);
            selection[i] = newWord;
        }
    }
    mod_sel = selection;
}

int main(int argc, char* argv[]) {
    ifstream dic(argv[1]);

    if (!dic) { // Verificar si el archivo se abrió correctamente
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    set<string> dictionary; // Declarar el conjunto para almacenar las palabras

    string word;
    while (dic >> word) { // Leer cada palabra del archivo
        dictionary.insert(word); // Insertar la palabra en el conjunto
    }

    dic.close(); // Cerrar el archivo
    string sel = "", mod_sel = "";
    getSelections(dictionary, sel, mod_sel);
    vector<vector<string>> partitions = separarPalabras(mod_sel, dictionary);

    if (partitions.empty()) {
        cout << "La cadena no se puede dividir en palabras del diccionario" << endl;
    } else {
        cout << "Todas las particiones posibles de la cadena en palabras del diccionario son:" << endl;
        for (vector<string> partition : partitions) {
            for (int i = 0; i < partition.size(); i++) {
                cout << partition[i];
                if (i < partition.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }

    return 0;
}
