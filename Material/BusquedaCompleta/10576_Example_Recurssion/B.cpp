// multiples casos hasta final de linea
// nos dan dos numeros, s, d
// maximizar una suma de s y d

// 12 meses, y en cada mes dos opciones (s, o -d);
// checar los 5 meses consecutivos sean < 0
// al final, imprimar la mayor suma posible o Deficit si es negativa

// supongamos que tengo una combinacion, como checo que es valida??
// un for, y la suma y ya

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll meses[12];
bool check() {
    // checar cada segmento de 5 meses
    for (int i = 0; i < 8; i++) {
        int deficit = 0;
        for (int j = 0; j < 5; j++) deficit += meses[i+j];
        if (deficit >= 0) return false;
    }
    return true;
}

ll ans = -1;
ll s, d;
void bt(ll i, ll suma) {
    if (i == 12) {
        //for (int i = 0; i < 12; i++) cout << meses[i] << ' ';
        if (check()) ans = max(ans,suma);
        return;
    }
    meses[i] = s;
    bt(i+1, suma + s);
    meses[i] = -1 * d;
    bt(i+1, suma - d);
    return;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (cin >> s >> d) {
        ans = -1;
        bt(0, 0);
        if (ans < 0) {
            cout << "Deficit\n";
            continue;
        }
        cout << ans << '\n';
    }
}
