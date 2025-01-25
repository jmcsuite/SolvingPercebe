#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

ll calc(vll& a, vll& b) {
    size_t n = min(a.size(), b.size());
    ll ans = 0;
    for (size_t i=0; i<n; i++) ans = min(ans, b[i] - a[i]);
    return ans;
}

void solve() {
    ll n,l,r; cin>>n>>l>>r;
    vll vl(n);
    for (int i=0; i<n; i++) cin>>vl[i];
    vll a,b,c;
    l--; r--;
    for (int i=0; i<l; i++) a.push_back(vl[i]);
    for (int i=l; i<=r; i++) b.push_back(vl[i]);
    for (int i=r+1; i<n; i++) c.push_back(vl[i]);

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    reverse(b.begin(), b.end());
    for (size_t i=1; i<a.size(); i++) a[i] += a[i-1];
    for (size_t i=1; i<b.size(); i++) b[i] += b[i-1];
    for (size_t i=1; i<c.size(); i++) c[i] += c[i-1];

    ll ans = min(calc(b, a), calc(b, c));
    ans += b[(int)b.size() - 1];
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while(t--) solve();
}
