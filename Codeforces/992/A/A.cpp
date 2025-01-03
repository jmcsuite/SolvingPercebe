#include <bits/stdc++.h>
using namespace std;


using ll = long long;
using pll = pair<ll,ll>;
void solve() {
    ll N,K; cin >> N >> K;
    vector<ll> vl(N);
    for (int i=0; i< N; i++) cin >> vl[i];
    map<ll,ll> mp;
    for (int i=0; i<N; i++) mp[vl[i]%K]++;
    for (pll p: mp) {
        if (p.second > 1) continue;
        for (int i=0; i<N; i++) {
            if (vl[i]%K == p.first) {
                cout << "YES\n";
                cout << ++i << '\n';
                return;
            }
        }
    }
    cout << "NO\n";
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        solve();
    }
}
