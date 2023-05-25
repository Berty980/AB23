//Nodo del espacio de soluciones (estado de la solución)
#pragma once

#include <set>
#include <vector>
#include <limits>

using namespace std;

class Pedido {
    public:
    int estacion_salida;
    int estacion_llegada;
    int num_pasajeros;

    int calcularIngreso() {
        return (estacion_llegada - estacion_salida) * num_pasajeros;
    }
};

class Node{
    public:
    set<int> pedidos_no_aceptados{};
    bool valido;
    int max_pedido_aceptado; //pedido con indice mayor entre los aceptados

    Node(int num_pedidos){
        for(int i = 0; i < num_pedidos; i++) pedidos_no_aceptados.insert(i);
        valido = true;
        max_pedido_aceptado = -1;
    }

    //crea un nodo con los pedidos no aceptados de el nodo n menos el pedido p (acepta el pedido p)
    Node(Node n, int p, vector<Pedido> pedidos, int ultima_estacion, int capacidad, int max_p_aceptado_padre){
        pedidos_no_aceptados = n.pedidos_no_aceptados;
        pedidos_no_aceptados.erase(p);
        valido = comprobarSiValido(pedidos, ultima_estacion, capacidad);
        if(p > max_p_aceptado_padre) max_pedido_aceptado = p;
    }

    //Función de estimación (coste infinito si nodo no valido)
    int ingresoEstimadoPedidosNoAceptados(vector<Pedido> pedidos){
        if(valido){
            int total = 0;
            for (const auto& pedido_no_aceptado : pedidos_no_aceptados) {
                
                if(pedido_no_aceptado < max_pedido_aceptado){
                    total += pedidos[pedido_no_aceptado].calcularIngreso();
                    //cout << "\t\t max_pedido_aceptado: " << max_pedido_aceptado << " pedido: " << pedido_no_aceptado << " ingreso total: " << total << endl; 
                }
                    
                //cout << "\t pedido " << pedido_no_aceptado << " ingreso " << pedidos[pedido_no_aceptado].calcularIngreso() << " ingreso total " << total << endl; 
            }
            return total;
        } else{
            return numeric_limits<int>::max();
        }        
    }

    //coste infinito si nodo no valido
    //coincide con la función de cota
    int ingresoPedidosNoAceptados(vector<Pedido> pedidos){
        if(valido){
            int total = 0;
            for (const auto& pedido_no_aceptado : pedidos_no_aceptados) {
                total += pedidos[pedido_no_aceptado].calcularIngreso();
                //cout << "\t pedido " << pedido_no_aceptado << " ingreso " << pedidos[pedido_no_aceptado].calcularIngreso() << " ingreso total " << total << endl; 
            }
            return total;
        } else{
            return numeric_limits<int>::max();
        }        
    }

    //comprueba si el nodo es una solución válida
    bool comprobarSiValido(vector<Pedido> pedidos, int ultima_estacion, int capacidad){
        set<int> pedidos_aceptados = getPedidosAceptados(pedidos);
        vector<int> tramos_recorrido(ultima_estacion, 0);
        
        for (const auto& pedido_aceptado : pedidos_aceptados) {
            //cout << "\t" << "pedido: " << pedido_aceptado << endl;
            for(int i = pedidos[pedido_aceptado].estacion_salida; i < pedidos[pedido_aceptado].estacion_llegada; i++){
                tramos_recorrido[i] += pedidos[pedido_aceptado].num_pasajeros;
                //cout << "\t" << "\t" << "tramo: " << i << " pasajeros: " << tramos_recorrido[i] << endl ;
                if(tramos_recorrido[i] > capacidad) return false;
            }
        }
        return true;
    }

    set<int> getPedidosAceptados(vector<Pedido> pedidos){
        set<int> aux{};
        
        for(int i = 0; i < pedidos.size(); i++){
            auto it = pedidos_no_aceptados.find(i);
            if (it == pedidos_no_aceptados.end()) aux.insert(i);
        }

        return aux;
    }
};