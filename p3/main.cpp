#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <random>

using namespace std;

vector<vector<string>> wordBreak(string s, set<string>& wordDict) {
    int n = s.length();
    vector<vector<vector<string>>> dp(n + 1);  // dp[i] = todas las particiones posibles de s[0:i-1] en palabras del diccionario
    dp[0] = {{}};  // la cadena vacía se puede dividir en una única partición vacía

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (!dp[j].empty() && wordDict.count(s.substr(j, i - j))) {
                string word = s.substr(j, i - j);
                for (auto& partition : dp[j]) {
                    partition.push_back(word);
                    dp[i].push_back(partition);
                    partition.pop_back();
                }
            }
        }
    }
    /*for (int i = 0; i <= n; i++) {
        cout << "i = " << i << endl;
        for (int j = 0; j < dp[i].size(); j++) {
            cout << "\t";
            for (int k = 0; k < dp[i][j].size(); k++) {
                cout << dp[i][j][k] << " ";
            }
            cout << endl;
        }
    }*/
    return dp[n];
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

    vector<vector<string>> partitions = wordBreak(mod_sel, dictionary);

    if (partitions.empty()) {
        cout << "La cadena no se puede dividir en palabras del diccionario" << endl;
    } else {
        cout << "Todas las particiones posibles de la cadena en palabras del diccionario son:" << endl;
        for (auto& partition : partitions) {
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
