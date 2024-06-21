// Multi casos, hasta 0, 0 
// while(cin >> N >> M, N || M)
// N, M. Despues N lineas, despues M, lineas

// Salida, si no hay respuesta escribir 
// Loowater is doomed!
// Si hay respuesta, escribir la suma de los caballeros.

// Greedy: Ordeno dragon , y caballero 
// Si hay match, hago match, si no, me salto al siguiente caballero

// como voy a iterar matches??? dos numeros i, j. 
// como voy a iterar y no pasarme??? check( i < N && j < M)
// que pasa si no hay match? j++
// que pasa si hay match? i++, j++, ans += caballero[j-1], contador++
// como checo, que si matche todos los dragones? un contador, contador == N

#include <bits/stdc++.h> // igual a #include <vector>,  #include <algorithm>, etc.
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0); // optimizar lectura cin, cout
    cin.tie(0);

    ll N, M;
    while (cin >> N >> M, N || M) {
        vector<ll> dragon(N);
        vector<ll> caballero(M);
        for (int i = 0; i < N; i++) cin >> dragon[i];
        for (int i = 0; i < M; i++) cin >> caballero[i];

        sort(dragon.begin(), dragon.end());
        sort(caballero.begin(), caballero.end());

        int i,j; i = j = 0;
        ll ans = 0;
        ll cont = 0;
        while (i < N && j < M) {
            if (caballero[j] >= dragon[i]) {
                i++;
                j++;
                ans += caballero[j-1];
                cont++;
            }
            else {
                j++;
            }
        }
        if (cont == N) {
            cout << ans << '\n';
        }
        else {
            cout << "Loowater is doomed!\n";
        }
    }
}
