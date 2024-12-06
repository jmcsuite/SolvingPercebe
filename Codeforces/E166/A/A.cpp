#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ll N;
    string s;
    cin >> N >> s;
    for (int i = 1; i < N; i++) {
        if (s[i] < s[i-1]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) solve();
}
