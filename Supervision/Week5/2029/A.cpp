#include <bits/stdc++.h>
using namespace std;
using ll = long long;


ll f(ll i) {
    assert(i > 0);
    return (1ll << (i-1)) - 1;
}

char other(char a, char b) {
    if ('A' != a && 'A' != b) return 'A';
    if ('B' != a && 'B' != b) return 'B';
    return 'C';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); ll N; cin>>N;
    string s; cin>>s;
    ll ans = 0;
    char c = 'A';

    for (int i=N-1; i >= 0; i--) {
        if (c == s[i]) continue;

        c = other(c, s[i]); 
        ans += f(i+1) + 1;
    }
    cout << ans << '\n';
}
