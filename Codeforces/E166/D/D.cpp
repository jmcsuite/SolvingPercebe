#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5;
ll vl[maxn];

void solve() {
    string s; cin >> s;
    ll N = s.size();
    vl[0] = 1;
    for (int i = 1; i < N; i++) vl[i] = (s[i] == '(' ? 1 : -1) + vl[i-1];
    map<ll,ll> mp;

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        ans += mp[vl[i]];
        auto it = mp.begin(); 
        while (it != mp.end() && it->first * 2 < vl[i]) {
            it = mp.erase(it);
        }
        mp[vl[i]]++;
    }
    cout << ans << '\n';
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) solve();
}
