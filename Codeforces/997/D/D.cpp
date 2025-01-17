#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using set_t = tree<ll,null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;

const int maxn = 1e5;
ll vl[maxn];
ll solve_pos(vll& v, ll x) {
    map<ll,ll> mp;
    mp[0] = 1;
    ll ans = 0;
    ll sum = 0;
    ll k = 0; 
    ll i = 0;
    while (vl[k] != x) k++;
    for (i=0; i<k; i++) {
        sum += v[i];
        mp[sum]++;
    }

    while (i < (int)v.size()) {
        ll xsum = sum;
        do {
            k++;
        } while(k <(int)v.size() && vl[k] != x);

        for (int z = i; z < k; z++) {
            xsum += v[z];
            ans += mp[xsum];
        }

        for (; i < k; i++) {
            sum += v[i];
            mp[sum]++;
        }
    }
    return ans;
}

void solve() {
    ll n; cin>>n;
    for (int i=0; i<n; i++) cin>>vl[i];
    ll ans = n * (n+1); 
    ans/=2;

    vll v(n);
    for (int k=1; k<10; k++) {
        for (int i=0; i<n; i++) v[i] = (vl[i] > k ? -1 : 1);
        bool se = false;
        for (int i=0; i<n; i++) if (vl[i] == k) se=true;
        if (!se) continue;
        ans -= solve_pos(v,k);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while (t--) solve();
}
