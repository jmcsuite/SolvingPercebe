#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5;

ll vl[2*maxn];
ll ans = 0;
ll f(ll x) {
    if (vl[x] == x) return x;
    return (vl[x] = f(vl[x]));
}

void un(ll i, ll j) {
    ll u = f(i); ll v = f(j);
    if (u == v) return;
    ans--;
    vl[u] = v;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M, Q; cin >> N >> M >> Q; 
    ans = N+M;
    for (int i = 0; i < N+M; i++) vl[i] = i;
    while (Q--) {
        ll a, b; cin >> a >> b; 
        a--; b = b + N - 1;
        un(a,b);
    }
    cout << ans - 1 << '\n';
}
