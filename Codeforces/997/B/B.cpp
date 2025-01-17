#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1000;
ll vadj[maxn][maxn];
ll sum[maxn];

void solve() {
    ll n; cin>>n;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            char x; cin>>x;
            vadj[i][j] = x-'0';
        }
    }
    for (int i=0; i<n; i++) sum[i] = 0;

    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) vadj[i][j] ^= 1;
    }

    vector<ll> ans(n);
    for (int i=0; i<n; i++) for (int j=0; j<n; j++) sum[i] += vadj[i][j];
    for (int i=0; i<n; i++) ans[sum[i]] = i+1;
    for (int i=0; i<n; i++) cout << ans[i] << (i+1 == n ? '\n' : ' ');
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while (t--) solve();
}
