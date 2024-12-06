#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const string contest = "ABCDEFG";
int main () {
    ll T; cin >> T; 
    while (T--) {
        map<ll,ll> mp;
        ll N, M; cin >> N >> M;
        string s; cin >> s;
        for (char c: s) mp[c]++;
        ll ans = 0;
        for (char c : contest) ans += (max(0ll, M-mp[c]));
        cout << ans << '\n';
    }
}
