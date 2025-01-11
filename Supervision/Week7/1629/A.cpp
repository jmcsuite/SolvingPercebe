#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 100; 
const int mod = 24 * 60;

ll d[maxn];
ll t[maxn];

vll vadj[maxn];
vll dvadj[maxn];

ll ss(ll i, ll x) {
    for (ll y: dvadj[i]) if (y >= x) return y;
    return 0;
}

ll nn(ll i, ll x) {
    for (ll y: vadj[i]) if (y >= x) return y;
    return vadj[i][0] + mod;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n; cin>>n; 
    --n;
    for (int i=0; i<n; i++) {
        int k; cin>>k;
        cin>>d[i]>>t[i];
        for (int j=0; j<k; j++) {
            char c;
            ll h,m; cin>>h>>c>>m;
            h = h*60 + m + d[i];
            dvadj[i].push_back(h); 
            dvadj[i].push_back(h + mod);
            h %= mod;
            vadj[i].push_back(h);
        }
        sort(vadj[i].begin(), vadj[i].end());
        sort(dvadj[i].begin(), dvadj[i].end());
    }
    ll ans=0; 
    ll days=0;
    for (int i=0; i<n; i++) {
        ans = (days != 0 ? nn(i,ans) : ss(i,ans));
        ans += t[i];
        while (ans >= mod) {
            days++; 
            ans-=mod;
        }
    }
    cout << ans + mod*days << '\n';
}
