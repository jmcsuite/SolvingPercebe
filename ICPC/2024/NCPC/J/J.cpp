#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    map<ll,ll> m;
    map<ll,ll> p; 
 
    ll N; cin>>N;
    vll vl(N);
    vll v2(N);
    for (int i = 0; i < N; i++) cin>>vl[i] >> v2[i];
    //for (int i = 0; i < N; i++) cin >> v2[i];
 
    if (N == 1) {
        if (vl[0] == 2 && v2[0] == 2) cout << "NO\n";
        else cout << "YES\n1 1\n";
        return 0;
    }
 
    for (int i = 0; i < N; i++) {
        m[vl[i]] = v2[i];
        p[v2[i]] = vl[i];
    }
 
    for (int i = 2; i <= 2*N; i+=2) {
        if (m.find(i) == m.end()) {
            cout << "YES\n";
            for (int j = 0; j < N; j++) {
                cout << i/2 << ' ' << j+1 << '\n';
            }
            return 0;
        }
 
        if (p.find(i) == p.end()) {
            cout << "YES\n";
            for (int j = 0; j < N; j++) {
                cout << j+1 << ' ' << i/2 << '\n';
            }
            return 0;
        }
    }
    ll x = m[2];
    cout << "YES\n";
    for (int i = 0; i < N-1; i++) {
        cout << i+2 << ' ' << x/2 << '\n';
    }
 
    ll y = 1;
    if ((x/2) % 2) y = 2;
    cout << (p[y*2] == 2 ? 2 : 1) << ' ' << y << endl;
}
