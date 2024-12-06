#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        string s; cin >> s;
        if (s.size() == 1) {
            cout << -1 << '\n';
            continue;
        }

        string ans="";
        for (int i = 1; i < (int)s.size(); i++) {
            if (s[i] == s[i-1]) {
                ans.push_back(s[i]);
                ans.push_back(s[i]);
                break;
            }
        }

        if (!ans.empty()) {
            cout << ans << '\n';
            continue;
        }

        if (s.size() == 2) {
            cout << -1 << '\n';
            continue;
        }

        for (int i=2; i < (int)s.size(); i++) {
            if (s[i] != s[i-2]) {
                ans.push_back(s[i-2]);
                ans.push_back(s[i-1]);
                ans.push_back(s[i]);
                break;
            }
        }

        if (!ans.empty()) {
            cout << ans << '\n';
            continue;
        }

        cout << -1 << '\n';
        continue;
    }
}
