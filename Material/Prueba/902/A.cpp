#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<string,ll> mp;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N;
    while (cin >> N) {
        string s; cin >> s;
        string ans;
        ll maxi = 0;
        for (int i = 0; i <= (int)s.size() - N; i++) {
            string x = s.substr(i, N);
            mp[x]++;
            if (mp[x] > maxi) ans = x;
            maxi = max(mp[x], maxi);
        }
        cout << ans << '\n';
    }
}
