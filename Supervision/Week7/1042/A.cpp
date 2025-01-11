#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 250;
ll bits[maxn][maxn];
ll sol[maxn][maxn];
ll ans[maxn];
ll n;
ll vis[maxn];

ll search(ll j) {
    for (int i=0; i<n; i++) if (bits[i][j] && !vis[i]) return i;
    return 0;
}

void elim(ll i, ll k) {
    for (int j=0; j<n; j++) sol[k][j] ^= sol[i][j];
    for (int j=0; j<n; j++) bits[k][j] ^= bits[i][j];
}

void solve() {
    for (int i=0; i<n; i++) sol[i][i] = 1;
    for (int j=0; j<n; j++) {
        ll x = search(j);
        vis[x] = true;
        for (int k=0; k<n; k++) {
            if (k == x) continue;
            if (bits[k][j]) elim(x,k);
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i=0; i<n; i++) {
        ll x;
        while(cin>>x, x!=-1) {
            --x;
            bits[i][x] = 1;
        }
    }

    solve(); 
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) ans[j] ^= sol[i][j];
    }
    vll p;
    for (int i=0; i<n; i++) if (ans[i]) p.push_back(i+1);

    for (size_t i=0; i<p.size(); i++) cout << p[i] << (i+1 == p.size() ? '\n' : ' ');
}
