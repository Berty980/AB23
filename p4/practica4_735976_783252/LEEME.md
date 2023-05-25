del Rincón de la Villa, Alonso  783252@unizar.es  a783252
Lardiés Getán, Alberto  735976@unizar.es  a735976

---------node.h-----------
Contiene las estructuras de datos y métodos relativos a los pedidos y los nodos del espacio de soluciones.

---------main_branch_and_bound-----------
Uso: main_branch_and_bound fichero_entrada fichero_salida
Descripción: se ciñe a las especificaciones del enunciado

---------main_brute_force-----------
Uso: main_brute_force fichero_entrada fichero_salida
Descripción: Análogo a main_branch_and_bound pero utiliza un algoritmo de fuerza bruta

---------test_generator-----------
Uso: test_generator n
Descripción: genera un fichero pruebas.txt con 2 (las pruebas del enunciado) + n pruebas. 
            Las n pruebas tendrán un tren de capacidad 10 y un número aleatorio de estaciones y pedidos.
            El programa se encarga de que cada pedido cumpla las restricciones del enunciado.

----------Script ejecutar.sh---------
Descripción: compila todos los fuentes y ejecuta main_branch_and_bound pruebas.txt resultados.txt
            Cuenta con una instrucción de ejecución de main_brute_force comentada pues termina cuando el SO mata el proceso.
            También está comentada la ejecución de test_generator 3 para no sobreescribir las pruebas reflejadas en la memoria.