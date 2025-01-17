#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--) {
        ll n,m; cin>>n>>m;
        ll a,b; cin>>a>>b;
        ll s1 = m; ll s2 = m;
        for (int i=1; i<n; i++) {
            cin>>a>>b;
            s1 += a;
            s2 += b;
        }
        cout << s1*2 + s2*2 << '\n';
    }
}
