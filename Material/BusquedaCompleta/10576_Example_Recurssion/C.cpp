// multiples casos hasta el final de linea
// Nos dan dos numeros s y d
// Maximizar una suma de s y d
// 12 meses, y en cada mes dos opciones (s o -d)
// Checar los 5 meses consecutivos sean <0
// Al final imprimir la mayor suma posible o deficit si es negativa

// Supongamos que tengo una combinacion, como checo es valida?
//  Un for, y la suma y ya

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll meses[12];
bool check()
{
    // Checar cada segmento de 5 meses
    for (int i = 0; i < 8; i++)
    {
        int deficit = 0;
        for (int j = 0; j < 5; j++)
        {
            deficit += meses[i + j];
        }
        if (deficit >= 0)
            return false;
    }
    return true;
}

ll ans = -1;
ll s, d;
void bt(ll i, ll suma)
{
    if (i == 12)
    {
        if (check())
            ans = max(ans, suma);
        return;
    }

    meses[i] = s;
    bt(i + 1, suma + s);
    meses[i] = -1 * d;
    bt(i + 1, suma - d);
}

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (cin >> s >> d)
    {
        ans = -1;
        bt(0, 0);
        if (ans <= 0)
        {
            cout << "Deficit\n";
            continue;
        }
        cout << ans << "\n";
    }

    return 0;
}

