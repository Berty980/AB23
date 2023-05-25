#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <queue>
#include <string>
#include <sstream>
#include "node.h"

using namespace std;

std::string to_string(const std::pair<Node, int>& element) {
    std::ostringstream oss;

    // Convertir el par (Node, int) a cadena de texto
    oss << "Node: { pedidos_no_aceptados = [";
    for (const auto& pedido : element.first.pedidos_no_aceptados) {
        oss << pedido << " ";
    }
    oss << "], valido = " << (element.first.valido ? "true" : "false") << " }, coste = " << element.second;

    return oss.str();
}

//comparador para la cola con prioridad de forma que el par (nodo, coste) de menor coste tiene mayor prioridad
struct NodeComparator {
    bool operator()(const pair<Node, int>& p1, const pair<Node, int>& p2) const {
        return p1.second > p2.second;
    }
};

//Buscamos el ingreso agregado mínimo de los pedidos no aceptados que restados al ingreso
//agregado de todos los pedidos nos da el ingreso agregado máximo de los pedidos aceptados
int buscarMaximoIngreso(vector<Pedido>& pedidos, int capacidad, int ultima_estacion) {
    
    std::priority_queue<pair<Node, int>, std::vector<pair<Node, int>>, NodeComparator> pq;

    Node estado_inicial(pedidos.size());
    int coste = estado_inicial.ingresoEstimadoPedidosNoAceptados(pedidos);
    int minimo_coste;
    int cota = estado_inicial.ingresoPedidosNoAceptados(pedidos);

    pq.emplace(estado_inicial, coste);

    while (!pq.empty()) {
        Node nodo_en_expansion = pq.top().first;
        pq.pop();

        for (const auto& pedido_no_aceptado : nodo_en_expansion.pedidos_no_aceptados) {
            Node nodo_hijo(nodo_en_expansion, pedido_no_aceptado, pedidos, ultima_estacion, 
                capacidad, nodo_en_expansion.max_pedido_aceptado);

            //Si la función de estimación es menor que la función de cota podamos
            if(nodo_hijo.ingresoEstimadoPedidosNoAceptados(pedidos) <= cota){
                pq.emplace(nodo_hijo, nodo_hijo.ingresoEstimadoPedidosNoAceptados(pedidos));

                //si es solución factible y su función de cota es menor que la cota actual
                if(nodo_hijo.valido && nodo_hijo.ingresoPedidosNoAceptados(pedidos) < cota){
                    cota = nodo_hijo.ingresoPedidosNoAceptados(pedidos);
                    
                } 
            } else{
                //cout << "RAMA PODADA"<< endl; 
            }
            
        }
        if (pq.empty() || pq.top().second >= cota){
            minimo_coste = cota;
            pq = std::priority_queue<pair<Node, int>, std::vector<pair<Node, int>>, NodeComparator>(); 
        }
    }
    //calculamos ingreso agregado maximo de los pedidos añadidos a partir del ingreso agregado minimo de los no añadidos
    int ingreso_ideal = 0;
    for(int i = 0; i < pedidos.size(); i++){
        ingreso_ideal += pedidos[i].calcularIngreso();
    }
    return ingreso_ideal - minimo_coste;
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Uso: transporte pruebas.txt resultados.txt" << endl;
        return 1;
    }

    string input_file = argv[1];
    string output_file = argv[2];

    ifstream input(input_file);
    ofstream output(output_file);

    int capacidad_tren, num_ultima_estacion, num_pedidos;
    while (input >> capacidad_tren >> num_ultima_estacion >> num_pedidos && capacidad_tren != 0) {
        vector<Pedido> pedidos(num_pedidos);
        for (int i = 0; i < num_pedidos; i++) {
            Pedido pedido;
            input >> pedido.estacion_salida >> pedido.estacion_llegada >> pedido.num_pasajeros;
            pedidos[i] = pedido;
        }

        int mejor_ingreso_total;

        auto start_time = chrono::steady_clock::now();
        
        mejor_ingreso_total = buscarMaximoIngreso(pedidos, capacidad_tren, num_ultima_estacion);

        auto end_time = chrono::steady_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end_time - start_time).count();

        output << mejor_ingreso_total << " " << duration << endl;
    }

    input.close();
    output.close();

    return 0;
}