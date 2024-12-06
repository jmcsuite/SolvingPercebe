#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 3e5;
ll der[maxn];
ll vl[maxn];
ll ans[maxn];

ll f(ll x) {
    if (vl[x] == x) return x;
    return vl[x] = f(vl[x]);
}

void un(ll a, ll b) {
    ll pa = f(a); ll pb = f(b);
    if (pa == pb) return;
    der[pa]=max(der[pa], der[pb]);
    vl[pb]=pa;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M; cin >> N >> M;
    for (int i = 0; i < N; i++) {
        vl[i] = i;
        der[i] = i+1;
        ans[i] = -1;
    }

    while(M--) {
        ll l,r,x; cin >> l >> r >> x; l--; x--;
        for (int i = l; i < x;) {
            if (ans[i] == -1) ans[i] = x;
            ll j = der[f(i)];
            if (j != x) un(i,j);
            i = j;
        }

        for (int i = x+1; i < r;) {
            if (ans[i] == -1) ans[i] = x;
            ll j = der[f(i)];
            if (j < r) un(i,j);
            i = j;
        }
    }

    for (int i = 0; i < N; i++) cout << ans[i]+1 << (i == N-1 ? '\n' : ' ');
}
