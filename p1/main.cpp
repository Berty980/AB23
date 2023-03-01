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

using namespace std;

const int blockSize = 8;

/*
 * https://regor.home.blog/2020/04/25/calculo-del-inverso-modular/
 * Calcula el inverso modular de a módulo b
 */
int invMod(int a, int b) {
    int r0 = a>b? a:b;
    int r1 = r0==a? b:a;
    int s0=1, s1=0, t0=0, t1=1;
 
    while (r1 != 0) {
        int r = r0 % r1;
        int q = int(r0/r1);
        int s = s0 - q * s1;
        int t = t0 - q * t1;
 
        r0 = r1;
        r1 = r;
        s0 = s1;
        s1 = s;
        t0 = t1;
        t1 = t;
    }
    if (r0 != 1) {
        cout << "Error" << endl;
    }
    return a<b? t0%b:s0%b;
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
    string b = "";
    auto ret = 0;
    for(auto i = bin.size(); i > 0; i--) {
        b += bin[i-1];
        ret += bin[i-1] * pow(2, bin.size() -i);
    }
    cout << "bin: " << b << ". int: " << ret << endl;
    return ret;
}

/*
 * Cifra el mensaje m con la clave k
 */
vector<int> encrypt(const string m, const vector<int> k) {
    auto ret = vector<int>();
    cout << m << endl;
    for(auto c : m){
        cout << "Caracter: " << c << flush;
        auto bin = int2bin(int(c));
        auto cif = 0;
        cout << ". binario: ";
        for(int i = 0; i < bin.size(); i++) {
            cif += bin[i] * k[i];
            cout << bin[i];
        }
        cout << endl;
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
        if(sum >= k_priv[i+1]) { 
            cout << "1" << endl;
            return false;
        }
    }
    if (N <= sum + k_priv[k_priv.size()-1]) return false;
    if (gcd(N, w) != 1) return false;
    return true; 
}

//Ejemplo de ejecución: cifrar_y_descifrar k_priv message
int main(int argc, char* argv[]) {
    
    string key(argv[1]);
    string messageFile(argv[2]);
    string output(argv[3]);
    ifstream kf(key);
    ifstream mf(messageFile);
    ofstream of(output);
    
    auto k_priv = vector<int>();
    for(auto i = 0; i < blockSize; i++) {
        int x;
        kf >> x;
        k_priv.push_back(x);
    }
    cout << "k_priv: ";
    for(auto c : k_priv){
        cout << " " << c;
    }
    cout << endl;

    int N, w;
    kf >> N;
    kf >> w;
    cout << "N: " << N << ". w: " << w << endl;
    
    if(!check_k_priv(k_priv, N, w)){
        cerr << "los componentes de la clave privada no cumplen las restricciones" << endl;
        return 1;
    }

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
    
    auto w_inv = invMod(w,N);
    auto k_pub = k_priv;
    for(int i = 0; i < k_pub.size(); i++)
        k_pub[i] = (w * k_pub[i]) % N;

    cout << "Mensaje a enviar: " + message << endl;
    auto encrypted = encrypt(message, k_pub);
    cout << "Mensaje cifrado:";
    for(auto c : encrypted){
        cout << " " << c;
    }
    cout << endl;
    auto decrypted = decrypt(encrypted, k_priv, N, w_inv);
    cout << "Mensaje descifrado: " + decrypted << endl;
} 
