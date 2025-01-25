#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

void solve() {
    ll n; cin>>n;
    vll vl(n);
    for (int i=0; i<n; i++) cin>>vl[i];
    sort(vl.begin(), vl.end());
    for (int i=2; i+1<n; i++) {
        if (vl[i] == vl[i+1]) {
            cout << vl[i] << ' ' << vl[i+1] << ' ' << vl[i-1] << ' ' << vl[i-2] << '\n';
            return;
        }
    }

    ll prev = vl[0];
    ll mindif = vl[3] - vl[0];
    ll a = vl[0]; 
    ll b = vl[3];
    for (int i = 3; i<n; i++) {
        if ((vl[i] - prev) < mindif) {
            mindif = vl[i] - prev;
            a = vl[i];
            b = prev;
        }
        prev = vl[i];
    }

    if (vl[1] == vl[2] && (vl[1] + vl[2] > mindif)) {
        cout << vl[1] << ' ' << vl[2] << ' ' << a << ' ' << b << '\n';
        return;
    }

    mindif = vl[3] - vl[2];
    a = vl[2];
    b = vl[3];
    prev = vl[2];
    for (int i = 3; i<n; i++) {
        if ((vl[i] - prev) < mindif) {
            mindif = vl[i] - prev;
            a = vl[i];
            b = prev;
        }
        prev = vl[i];
    }
    if (vl[0] == vl[1] && (vl[0] + vl[1] > mindif)) {
        cout << vl[0] << ' ' << vl[1] << ' ' << a << ' ' << b << '\n';
        return;
    }
    cout << -1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while(t--) solve();
}
