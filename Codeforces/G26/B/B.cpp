#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        string s; cin >> s; ll N = s.size();
        if (s[0] != '1' || s[N-1] == '9') {
            cout << "NO\n";
            continue;
        }
        bool ans = true;
        for (int i = 1; i < N-1; i++) if (s[i] == '0') ans = false;
        cout << (ans ? "YES\n" : "NO\n");
    }
}
