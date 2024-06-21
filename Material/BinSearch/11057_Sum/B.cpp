// 2 <= N <= 10000
// Siempre hay solucion

// a + b = N
// b = N - a. -> yo itero por 'a' y busco 'b'.
// Como encuentro b? Set, Map? Otro puntero de atras hacia adelante? O Busqueda binera, en mi array ordenado

// Busqueda Binaria
// 1.- Ordenar
// 2.- [1, 2 , 3 ]. M = 4 Tener cuidado no contarme dos veces.
// ah, si estoy en i, mi primer rango es [i+1, N]
// que es lo que busco? N-a. peroooo, en busqueda binaria no puedo hacer eso. 
//  el entero <= N-a. Ya que lo tengo, verifico, que la suma sea N

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 10000;
ll vl[maxn];
ll N;

bool bus(ll i, ll x) {
    ll inc = N;
    while (inc) {
        if (i + inc < N && vl[i+inc] <= x) i += inc;
        else inc/=2;
    }
    return vl[i] == x;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (cin >> N) {
        for (int i = 0; i < N; i++) cin >> vl[i];
        ll M; cin >> M;

        sort(vl, vl + N);
        ll ans;
        for (int i = 0; i < N; i++) {
            if (i == N-1) break;
            if (bus(i+1, M-vl[i])) ans = vl[i];
        }
        cout << "Peter should buy books whose prices are " << ans << " and " << M-ans << ".\n\n";
    }
}
