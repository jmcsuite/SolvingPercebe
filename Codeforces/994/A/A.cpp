#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

 void solve() {
     ll N; cin >> N;
     vll vl(N); 
     for (int i=0; i<N; i++) cin >> vl[i];

     ll cc = 0;
     for (int i=0; i<N; i++) {
         if (vl[i] == 0) continue;
         if (i == 0 || vl[i-1] == 0) cc++;
     }

     cout << min(cc, 2ll) << '\n';
 }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while (T--) solve();
}


