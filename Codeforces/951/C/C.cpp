#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 50;
ll vl[maxn];

ll gcd(ll a, ll b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return gcd(b%a, a);
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        for (int i = 0; i < N; i++) cin >> vl[i];
        ll mcm = 1;
        for (int i = 0; i < N; i++) {
            mcm /= gcd(vl[i], mcm);
            mcm *= vl[i];
        }

        ll s = 0; 
        for (int i = 0; i < N; i++) s += mcm / vl[i];
        if (s >= mcm) {
            cout << -1 << '\n';
            continue;
        }
        for (int i = 0; i < N; i++) cout << mcm / vl[i] << (i == N-1 ? '\n' : ' ');
    }
}
