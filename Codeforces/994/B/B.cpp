#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool check(string a, string s) {
    for (int i=0; i<(int)a.size(); i++) {
        if (s[i] == '.') continue;
        if (s[i] != a[i]) return false;
    }
    return true;
}

void solve() {
    ll N; cin>>N;
    string s; cin >> s;
    string a,b,c,d;
    for (int i=0; i<N; i++) a.push_back('s');
    for (int i=0; i<N; i++) b.push_back('p');
    c = a;
    d = b;
    if (N == 1) {
        cout << "YES\n";
        return;
    }

    c[N-1] = 'p';
    d[0] = 's';

    if (check(a,s) || check(b,s) || check(c,s) || check(d,s)) {
        cout << "YES\n";
    }
    else {
        cout << "NO\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll T; cin>>T;
    while(T--) solve();
}
