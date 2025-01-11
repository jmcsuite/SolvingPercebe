#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

const int maxn = 1e5;
ll vl[maxn];

void solve() {
    ll n,k; cin>>n>>k;
    for (int i=0; i<n; i++) cin>>vl[i];
    map<ll,ll> mp;
    for (int i=0; i<n; i++) mp[vl[i]]++;
    ll ans = mp.size();

    vector<ll> freq;
    for (pll p: mp) freq.push_back(p.second);
    sort(freq.begin(), freq.end());

    for (ll x: freq) {
        if (x > k) break;
        k-=x;
        ans--;
    }
    cout << max(ans, 1ll) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while (T--) solve();
}
