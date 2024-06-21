#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        string s; cin >> s;
        int ans = 0;
        int inc = 0;
        for (char c : s) {
            if (c == 'X') {
                inc = 0;
                continue;
            }
            ans += ++inc;
        }
        cout << ans << '\n';
    }
}
