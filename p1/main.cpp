#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

// https://regor.home.blog/2020/04/25/calculo-del-inverso-modular/
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

vector<int> int2bin(int i){
    auto ret = vector<int>(5, 0);
    auto j = 1;
    while(i > 0) {
        ret[ret.size() - j] = i%2;
        i /= 2;
        j++;
    }
    return ret;
}

int bin2int(vector<int> bin){
    auto ret = 0;
    for(auto i = bin.size(); i > 0; i--) {
        ret += bin[i-1] * pow(2, bin.size() -i);
    }
    return ret;
}

vector<int> cifrar(const string m, const vector<int> k) {
    auto ret = vector<int>();
    for(auto c : m){
        auto bin = int2bin(int(c) - int('@'));
        auto cif = 0;
        for(int i = 0; i < bin.size(); i++) {
            cif += bin[i] * k[i];
        }
        ret.push_back(cif);
    }
    return ret;
}

string descifrar(vector<int> m, const vector<int> k, const int n, const int w_inv) {
    string ret = "";
    for(auto i = 0; i < m.size(); i++)
        m[i] = (m[i] * w_inv) % n;
    
    for(auto c : m) {
        auto bin = vector<int>(5, 0);
        for(auto i = k.size(); i > 0; i--) {
            if(c >= k[i-1]) {
                bin[i-1] = 1;
                c -= k[i-1];
            }
        }
        ret += char(bin2int(bin) + 64);
    }
    return ret;
}

int main() {
    auto n = 5;
    const auto k_priv = vector<int>{2, 3, 7, 15, 31};
    const auto N = 61;
    const auto w = 17;

    auto w_inv = invMod(w,N);
    auto k_pub = k_priv;
    for(int i = 0; i < k_pub.size(); i++)
        k_pub[i] = (w * k_pub[i]) % N;

    string mensaje = "HOLA";
    cout << "Mensaje a enviar: " + mensaje << endl;
    auto cifrado = cifrar(mensaje, k_pub);
    cout << "Mensaje cifrado:";
    for(auto c : cifrado){
        cout << " " << c;
    }
    cout << endl;
    auto descifrado = descifrar(cifrado, k_priv, N, w_inv);
    cout << "Mensaje descifrado: " + descifrado << endl;
} 