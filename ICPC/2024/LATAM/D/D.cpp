#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    ll ndiv = 0;
    for (ll i=1; i*i<=N; i++) {
        if (N%i) continue;
        ndiv++;
        if (N/i != i) ndiv++;
    }

    ll pdiv = 0;
    for (ll i = 2; i*i <= N; i++) {
        if (N%i) continue;
        pdiv++;
        while (N%i == 0) N/=i;
    }
    if (N != 1) pdiv++;

    if (ndiv%2) {
        cout << "N\n";
        return 0;
    }

    if (pdiv == 1) {
        cout << "Y\n";
        return 0;
    }

    if (ndiv > 4) cout << "N\n";
    else cout << "Y\n";
}
