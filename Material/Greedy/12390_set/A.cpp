// N, B. N <= 500, 000
// B <= 2e6

// Multi casos, hasta -1 -1a

// Salida, un numero, max. 

// Mantener el maximo siempre. asignar un ballot a la ciudad que tenga el maximo
// Actualizar maximo.

// Actualizar maximo????
// Si antes tenia, ballots[i], ahora tengo ballots[i]+1; mantengo por cada ciudad cuantos votos
// Nuevo valor es poblacion[i] / ballots[i] ????
// Nuevo valor, es poblacion[i] / ballots[i] + (1 si no es divisible)
// Nuevo valor, ............................ + (1 if (poblacion[i]%ballots[i]))

// Ya tengo valores nuevos, ahora como mantengo maximo.
// Set. set de que? de valores locales? necesito, set del valor y de la ciudad, ordenado por valor. 
// Teniendo el set, como obtengo el maximo? pair<ll,ll> a = *(--st.end());
// Teniendo el set, como quito??? st.erase(a); st.insert(a);

// priority_queue
// Como tengo el maximo? pair<ll,ll> a = pq.top();
// Como lo quito? pq.pop();
// Como inserto? pq.push({});


//Voy a asignar un ballot, al maximo. Cuantas asignaciones???
// [N+1, B]

// como inicializo??
// Cada ciudad un ballot
// El set, le agrego el maximo local de cada ciudad

// Al final como imprimo respuesta? *(--st.end()).first
#include <bits/stdc++.h>
using namespace std;
using ll = int;
const int maxn = 500000;

ll poblacion[maxn];
ll ballots[maxn];

// Division Techo
ll form(ll x) {
    ll v = poblacion[x] / ballots[x];
    if (poblacion[x] % ballots[x]) v++;
    return v;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); // fast cin cout
    ll N, B;
    while (cin >> N >> B, (N != -1) && (B != -1)) {
        for (int i = 0; i < N; i++) cin >> poblacion[i];
        
        // init
        priority_queue<pair<ll,ll>> pq;
        for (int i = 0; i < N; i++) ballots[i] = 1;
        for (int i = 0; i < N; i++) pq.push({form(i), i});

        // algo
        for (int i = N+1; i <= B; i++) {
            pair<ll,ll> maximo = pq.top();
            pq.pop();
            ballots[maximo.second]++;
            pq.push({form(maximo.second), maximo.second});
        }

        // respuesta
        cout << pq.top().first << '\n';
    }
}
