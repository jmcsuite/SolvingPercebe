#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e5;
ll vl[maxn];
ll b[maxn];
ll s1[maxn];
ll s2[maxn];

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
        if (N == 3) {
            cout << "YES\n";
            continue;
        }
        for (int i = 0; i < N-1; i++) b[i] = gcd(vl[i], vl[i+1]);
        s1[0] = 1;
        for (int i = 1; i < N-1; i++) {
            if (s1[i-1] == 0 || b[i] < b[i-1]) s1[i] = 0;
            else s1[i] = 1;
        }

        s2[N-2] = 1;
        for (int i = N-3; i >= 0; i--) {
            if (s2[i+1] == 0 || b[i] > b[i+1]) s2[i] = 0;
            else s2[i] = 1;
        }
        if (s2[1] || s1[N-3]) {
            cout << "YES\n";
            continue;
        }

        bool se = false;
        for (int i = 1; i < N-1; i++) {
            bool t = true;
            ll nb = gcd(vl[i-1], vl[i+1]);
            if (i > 1 && nb < b[i-2]) t = false;
            if (i > 1 && s1[i-2] == 0) t = false;
            if (i < N-2 && nb > b[i+1]) t = false;
            if (i < N-2 && s2[i+1] == 0) t = false;
            if (t) se = true;
        }
        if (se) cout << "YES\n";
        else cout << "NO\n";
    }
}
