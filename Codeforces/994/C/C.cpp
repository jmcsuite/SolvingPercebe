#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ll N, x,y;
    cin >> N >> x >> y; 
    --x; --y;

    vector<ll> vl(N);
    for (int i=1; i<N; i+=2) vl[i] = 1;
    if (N%2) vl[N-1] = 2;

    if (vl[x] == vl[y]) {
        vl[y] = 2;
        if (N%2) {
            for (int i=y+1; i<N; i++) vl[i] = (i+1)%2;
        }
    }

    for (int i=0; i<N; i++) cout << vl[i] << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while (T--) solve();
}
