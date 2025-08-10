#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

const int maxn = 5e5 + 5;
ll a[maxn];
ll b[maxn];
ll c[maxn];
ll d[maxn];
ll tmp[maxn];

ll n;
ll temp[maxn];
ll inv_count(ll arr[maxn]) {
    ll ans = 0;
    for (ll k=0; (1<<k)<n; k++) {
        for (ll z=0; z<n; z+=(1<<(k+1))) {
            ll h=z;
            ll i=z;
            ll j=z+(1<<k);
            while (1) {
                bool validj = true;
                bool validi = true;
                if (i >= n || i >= z + (1<<k)) validi=false;
                if (j >= n || j >= z + (1<<(k+1))) validj=false;
                if ((!validi) && (!validj)) break;
                if (validi && !validj) {
                    tmp[h++] = arr[i++];
                    continue;
                }
                if (validj && !validi) {
                    tmp[h++] = arr[j++];
                    continue;
                }
                if(arr[i] < arr[j]) {
                    tmp[h++] = arr[i++];
                    continue;
                }
                tmp[h++] = arr[j++];
                ans += (z+(1<<k)) - i;
            }
        }
        for (int i=0; i<n; i++) arr[i] = tmp[i];
    }
    return ans;
}

void solve() {
    cin>>n;
    for(int i=0; i<n; i++) cin>>a[i];
    for (int i=0; i<n; i++) cin>>b[i];

    for (int i=0; i<n; i++) a[i]--;
    for (int i=0; i<n; i++) b[i]--;
    for (int i=0; i<n; i++) c[a[i]] = b[i];
    for (int i=0; i<n; i++) d[b[i]] = a[i];

    ll A = inv_count(a);
    ll B = inv_count(b);
    ll C = inv_count(c);
    ll D = inv_count(d);
    if (A > B) {
        swap(A,B);
        swap(C,D);
    }
    cout << (C == (B-A) ? "Yes\n" : "No\n");
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while (t--) solve();
}
