del Rincón de la Villa, Alonso  783252@unizar.es  a783252
Lardiés Getán, Alberto  735976@unizar.es  a735976

---------main-----------
Uso: main -i archivo_entrada -o archivo_salida [-l longitud] [-p probabilidad]
Descripción: dado un diccionario de palabras en un fichero genera una combinación aleatoria (cuya longitud es la longitud del diccionario dividido entre 10 o el valor del parámetro l si lo tiene) de palabras del diccionario. Si tiene parámetro p, éste se usa para calcular la probabilidad de modificar cada caracter de cada palabra. Una vez hecho esto busca las particiones que puede hacer de la frase en palabras del diccionario y muestra por pantalla éste resultado y otras métricas importantes. También guarda esa información en un fichero, donde también escribe el contenido de las particiones encontradas.

---------dictionary_generator-----------
Uso: gen n out_file

Genera un diccionario de n palabras formadas por un número aleatorio de caracteres y lo guarda en out_file

----------Script ejecutar.sh---------
Descripción: compila el programa anterior y lo ejecuta para distintas combinaciones de los parámetros (descritas en profundidad en la memoria)