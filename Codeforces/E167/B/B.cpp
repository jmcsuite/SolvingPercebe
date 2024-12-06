#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll sol(const string& a, string b) {
    int i,j;
    for (i = j = 0; i < (int)a.size(); i++) {
        if (a[i] == b[j]) j++;
    }
    return j;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        string a, b; cin >> a >> b;
        ll tot = a.size() + b.size();
        ll ans = tot;
        for (int i = 0; i < (int)b.size(); i++) {
            ans = min(ans, tot - sol(a,b.substr(i)));
        }
        cout << ans << '\n';
    }
}
