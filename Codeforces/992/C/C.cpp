#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool les(ll x, ll k) {
    ll cant = 1; 
    if (x <= 0) return (1<k);
    x--;
    while ((cant < k) && x) {
        cant*=2;
        x--;
    }
    return cant < k;
}

ll calc(ll x) {
    if (x <= 0) return 1;
    x--;
    ll cant = 1;
    while (x) {
        cant*=2;
        x--;
    }
    return cant;
}


void solve() {
    ll N, K; 
    cin >> N >> K;
    if (les(N,K)) {
        cout << -1 << '\n';
        return;
    }
    vector<ll> vl(N); 
    ll l = 0; 
    ll r = N-1;

    for (int i=0; i<N; i++) {
        if (les(N-i-1, K)) {
            K -= calc(N-i-1);
            vl[r] = i+1;
            r--;
        }
        else {
            vl[l] = i+1;
            l++;
        }
    }

    for (int i =0; i<N; i++) cout << vl[i] << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--) solve();
}
