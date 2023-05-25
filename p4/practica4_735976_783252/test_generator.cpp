#include <iostream>
#include <fstream>
#include <random>

using namespace std;

void generar_bloque(ofstream& f, int capacidad_tren, int max_num_ultima_estacion, int max_num_pedidos) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> num_ultima_estacion(2, max_num_ultima_estacion);
    uniform_int_distribution<int> num_pedidos(5, max_num_pedidos);
    
    int num_ultima_estacion_generado = num_ultima_estacion(gen);
    int num_pedidos_generados = num_pedidos(gen);

    uniform_int_distribution<int> estaciones_salida(0, num_ultima_estacion_generado - 1);
    uniform_int_distribution<int> pasajeros(1, capacidad_tren);

    f << capacidad_tren << " " << num_ultima_estacion_generado << " " << num_pedidos_generados << endl;

    for (int i = 0; i < num_pedidos_generados; i++) {
        int estacion_salida = estaciones_salida(gen);

        //generamos la estación de llegada de forma que sea al menos 1 mayor a la de salida y menor o igual a la última
        uniform_int_distribution<int> estaciones_llegada(estacion_salida, max_num_ultima_estacion - 1);
        int estacion_llegada = estaciones_llegada(gen) + 1;

        int num_pasajeros = pasajeros(gen);

        f << estacion_salida << " " << estacion_llegada << " " << num_pasajeros << endl;
    }

}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Uso: test_generator <num_bloques>" << endl;
        return 1;
    }

    int num_bloques = atoi(argv[1]);

    if (num_bloques <= 0) {
        cout << "El número de bloques debe ser un entero positivo." << endl;
        return 1;
    }

    ofstream f("pruebas.txt");

    int capacidad_tren = 10; //el tamaño del problema no depende de ella, la dejamos en 10
    int max_num_ultima_estacion = 7;
    int max_num_pedidos = 22;

    //hardcodeamos las pruebas del enunciado para comprobar la corrección

    f << "10 3 5\n0 2 1\n0 3 2\n1 3 3\n1 2 4\n2 3 10\n10 5 6\n3 5 10\n2 4 9\n1 3 4\n0 2 5\n2 5 8\n3 4 2" <<endl;

    for (int i = 0; i < num_bloques; i++) {     
        generar_bloque(f, capacidad_tren, max_num_ultima_estacion, max_num_pedidos);
    }
    f << "0 0 0" << endl;
    f.close();

    return 0;
}