#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vll vl;
    for (ll i = 0; i <= 31; i++) {
        ll n  = (1LL << i);
        while (n <= (1LL << 31)) {
            vl.push_back(n);
            n*=3;
        }
    }
    sort(vl.begin(), vl.end());

    ll M;
    while (cin >> M, M) {
        ll ini = vl.size();
        ll dis = ini;
        while (dis) {
            if (ini - dis >= 0 && vl[ini-dis] >= M) ini-=dis;
            else dis/=2;
        }
        cout << vl[ini] << '\n';
    }
}
