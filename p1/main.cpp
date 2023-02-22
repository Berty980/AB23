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

vector<int> cifrar(const string m, const vector<int> k) {
    auto ret = vector<int>();
    for(auto c : m){
        auto x = int2bin(int(c) - int('@'));
        auto cif = 0;
        for(int i = 0; i < x.size(); i++) {
            cif += x[i] * k[i];
        }
        ret.push_back(cif);
    }
    return ret;
}

int main() {
    auto n = 5;
    const auto vol = vector<int>{2, 3, 7, 15, 31};
    const auto N = 61;
    const auto w = 17;

    auto w_inv = invMod(w,N);
    auto k_pub = vol;
    for(int i = 0; i < k_pub.size(); i++)
        k_pub[i] = (w * k_pub[i]) % N;

    string mensaje = "HOLA";
    cout << "Mensaje a enviar: " + mensaje << endl;
    auto cifrado = cifrar(mensaje, k_pub);
    cout << "Mensaje cifrado: " << cifrado[0];
    for(auto i = 1; i < cifrado.size(); i++){
        cout << ", " << cifrado[i];
    }
    cout << endl;

} 