#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

struct Node {
    int id;
    bool ag;
    Node *left, *right;
    Node(int id) : id(id), ag(false), left(nullptr), right(nullptr){}
};

Node* getTree(int id, int depth) {
    if (id > pow(2, depth) - 1) return nullptr;
    auto node = new Node(id);
    node->left = getTree(2 * id, depth);
    node->right = getTree(2 * id + 1, depth);
    return node;
}

int getBallPosition(Node* node, int ball) {
    if (node->left == nullptr) return node->id;
    auto left = !node->ag;
    node->ag = !node->ag;
    if (left) return getBallPosition(node->left, ball);
    else return getBallPosition(node->right, ball);
}

vector<int> getBallPositions(int balls, Node* root) {
    vector<int> positions(balls);
    for (int i = 0; i < balls; i++) {
        positions[i] = getBallPosition(root, i);
    }
    return positions;
}

int main(int argc, char* argv[]) {

    auto maxReps = 100;

    if (argc < 2)
      cout << "Uso: pinball <pruebas> <resultados>" << endl
           << "\tpruebas: nombre del fichero que contiene los casos de prueba" << endl
           << "\tresultados: nombre del fichero donde se escribirán los resultados de los casos de prueba" << endl;
    
    string tests(argv[1]);
    string results(argv[2]);
    ifstream p("pruebas/" + tests);
    ofstream r("resultados/" + results);
    
    if (!p.is_open()) { // Comprobamos que se ha abierto correctamente
        cout << "Error al abrir el archivo de pruebas." << endl;
        return 1;
    }

    auto test = 1;
    string data;
    while (getline(p, data)) { // Leemos cada línea del archivo
        int P, n;
        sscanf(data.c_str(), "%d %d", &P, &n);
        
        auto t_tree = chrono::nanoseconds(0);
        auto t_pos = chrono::nanoseconds(0);
        auto positions = vector<int>();
        
        for (int i = 0; i < maxReps; i++) {
            auto t0 = chrono::high_resolution_clock::now();
            auto root = getTree(1, P);
            auto t1 = chrono::high_resolution_clock::now();

            t_tree += chrono::duration_cast<chrono::nanoseconds>(t1 - t0);

            t0 = chrono::high_resolution_clock::now();
            positions = getBallPositions(n, root);
            t1 = chrono::high_resolution_clock::now();
            
            t_pos += chrono::duration_cast<chrono::nanoseconds>(t1 - t0);
        }

        r << "Prueba " << test << endl;
        r << "\tProfundidad: " << P << endl;
        r << "\tBolas: " << n << endl;
        r << "\tTiempo de generación del árbol: " << t_tree.count()/maxReps * 1e-6 << " us " << endl;
        r << "\tTiempo de cálculo de posiciones: " << t_pos.count()/maxReps * 1e-6 << " us " << endl;
        r << "\tPosición de las bolas: ";
        r << 1 << ": " << positions[0];
        for (int i = 2; i <= n; i++) {
            r << ", " << i << ": " << positions[i-1];
        }
        r << endl << endl;

        test++;
    }

    p.close();
    r.close();
    return 0;
}