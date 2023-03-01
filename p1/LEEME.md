del Rincón de la Villa, Alonso  783252@unizar.es  a783252
Lardiés Getán, Alberto  735976@unizar.es  a735976

---------Programa cifrar_y_descifrar-----------

Uso: cifrar_y_descifrar clave_privada mensaje

Descripción: dada una clave privada presente en un fichero con formato:
e
N
w
(Siendo e la mochila fácil {e1,e2,...,en}, N > Sum(e) y mcd(N, w) = 1)
El programa genera la clave pública a partir de esta, encripta el mensaje pasado como parámetro y lo desencripta con la clave privada.
Mostrará por la salida estandar si el mensaje inicial coincide con el mensaje desencriptado y los tiempos de cifrado y descifrado.


---------Programa test_cases_generator-------------

Uso: test_cases_generator tamaño_mensaje fichero_salida

Descripción: genera un mensaje de caracteres ascii aleatorios y escribibles

----------Script ejecutar.sh---------

Descripción: compila los dos programas anteriores, utiliza test_cases_generator para generar mensajes de tamaños 10, 100, 1000, 10000 y 100000 y ejecuta cifrar_y_descifrar con keys/key1.txt y cada mensaje generado y el útlimo mensaje con keys/wrongKey.txt