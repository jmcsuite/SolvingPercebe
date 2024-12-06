#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    map<char, int> err; 
    map<char, int> cc;

    string s;
    cin >> s;
    ll N; cin >> N;
    for (int i = 0; i < N; i++) {
        char a; ll x; cin >> a >> x;
        err[a] = x;
    }

    ll ans = s.size();
    for (char c: s) {
        if (err.find(c) == err.end()) continue;
        if (cc[c] == 0) {
            ans++; 
            cc[c] = err[c]-1;
        }
        cc[c]--;
    }
    cout << ans << '\n';
}
