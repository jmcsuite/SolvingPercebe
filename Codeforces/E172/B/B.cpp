#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll T; cin >> T;
    while(T--) {
        ll N; cin >> N;
        vll vl(N);
        for (int i=0; i<N; i++) cin>>vl[i];
        map<ll,ll> mp;
        for (int i=0; i<N; i++) mp[vl[i]]++;
        ll c1 = 0;
        ll c2 = 0;
        for (pll p: mp) {
            if (p.second == 1) c1++;
            else c2++;
        }

        ll ans = ((c1+1)/2)*2 + c2;
        cout << ans << '\n';
    }
}
