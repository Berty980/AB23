#include <cmath>
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>

using namespace std;

const int blockSize = 8;

/*
 * https://www.lawebdelprogramador.com/foros/Dev-C/1549476-Ayuda-Funcion-Inverso-Multiplicativo.html
 * Calcula el inverso modular de a módulo b
 */
 int invMod(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;

    return x1;
}

/*
 * Devuelve el entero representado por la codificación binaria bin
*/
vector<int> int2bin(int i){
    auto ret = vector<int>(blockSize, 0);
    auto j = 1;
    while(i > 0) {
        ret[ret.size() - j] = i%2;
        i /= 2;
        j++;
    }
    return ret;
}

/*
 * Devuelve la codificación en bits de l entero i
 */
int bin2int(vector<int> bin){
    auto ret = 0;
    for(auto i = bin.size(); i > 0; i--) {
        ret += bin[i-1] * pow(2, bin.size() -i);
    }
    return ret;
}

/*
 * Cifra el mensaje m con la clave k
 */
vector<int> encrypt(const string m, const vector<int> k) {
    auto ret = vector<int>();
    for(auto c : m){
        auto bin = int2bin(int(c));
        auto cif = 0;
        for(int i = 0; i < bin.size(); i++) {
            cif += bin[i] * k[i];
        }
        ret.push_back(cif);
    }
    return ret;
}

/*
 *Descifra el mensaje m con la clave privada k y los enteros N y w'
 */
string decrypt(vector<int> m, const vector<int> k, const int n, const int w_inv) {
    string ret = "";
    for(auto i = 0; i < m.size(); i++)
        m[i] = (m[i] * w_inv) % n;

    for(auto c : m) {
        auto bin = vector<int>(blockSize, 0);
        for(auto i = k.size(); i > 0; i--) {
            if(c >= k[i-1]) {
                bin[i-1] = 1;
                c -= k[i-1];
            }
        }
        ret += char(bin2int(bin));
    }
    return ret;
}

bool check_k_priv(vector<int> k_priv, int N, int w){
    int sum = 0;
    for(int i = 0; i < k_priv.size()-1; i++){
        sum += k_priv[i];
        if(sum >= k_priv[i+1]) return false;
    }
    if (N <= sum + k_priv[k_priv.size()-1]) return false;
    if (__gcd(N, w) != 1) return false;
    return true;
}

//Ejemplo de ejecución: cifrar_y_descifrar k_priv message
int main(int argc, char* argv[]) {

    if (argc < 2) {
      cout << "Uso: cifrar_y_descifrar <fichero_clave> <fichero_mensaje>" << endl;
      cout << "\fichero_clave: nombre del fichero que contiene la clave privada" << endl;
      cout << "\tfichero_mensaje: nombre del fichero que contiene el mensaje" << endl;
    }

    string key(argv[1]);
    string messageFile(argv[2]);
    ifstream kf(key);
    ifstream mf(messageFile);

    //Lectura de argumentos
    auto k_priv = vector<int>();
    for(auto i = 0; i < blockSize; i++) {
        int x;
        kf >> x;
        k_priv.push_back(x);
    }

    int N, w;
    kf >> N;
    kf >> w;

    //Comprobar si los valores de la clave privada cumplen las restricciones
    if(!check_k_priv(k_priv, N, w)){
        cerr << "Los componentes de la clave privada no cumplen las restricciones" << endl;
        return 1;
    }

    //Leer mensaje
    unsigned long long int read_bytes = 45 * 1024 *1024;
    char* memblock;
    string message = "";
    while(!mf.eof())
    {
        memblock = new char[read_bytes];
        mf.read(memblock, read_bytes);
        string str(memblock);
        message += str;
        delete [] memblock;
    }

    // Calcular la clave pública a partir de la clave privada
    auto k_pub = k_priv;
    for(int i = 0; i < k_pub.size(); i++)
        k_pub[i] = (w * k_pub[i]) % N;

    // Calcular el inverso de w módulo N
    auto w_inv = invMod(w,N);

    auto t0 = std::chrono::high_resolution_clock::now();
    auto encrypted = encrypt(message, k_pub);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t_encrypt = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0);

    t0 = std::chrono::high_resolution_clock::now();
    auto decrypted = decrypt(encrypted, k_priv, N, w_inv);
    t1 = std::chrono::high_resolution_clock::now();
    auto t_desencrypt = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0);;

    if(decrypted == message){
        cout << "El mensaje desencriptado coincide con el original" << endl;
        cout << "Tiempo de cifrado: " << t_encrypt.count() * 1e-6 << " ms " << endl;
        cout << "Tiempo de descifrado: " << t_desencrypt.count() * 1e-6 << " ms " << endl;
        cout << "Tiempo total: " << (t_encrypt + t_desencrypt).count() * 1e-6 << " ms " << endl;
    }
}
