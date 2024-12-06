#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 2e5 + 10;
const int mod = 999999229;
ll hh[maxn];
ll rev[maxn];

ll bin_exp(ll a,ll x) {
    ll ans = 1;
    while (x) {
        if (x%2) ans = (ans*a)%mod;
        a = (a*a)%mod;
        x/=2;
    }
    return ans;
}

ll inv;
// [l, r];
bool check(ll l, ll r, ll base, ll N) {
    if (l > r) return true;
    ll h1 = hh[r];
    if (l > 0) h1 = (h1 - hh[l-1])%mod;
    h1 = (h1 * bin_exp(inv, l))%mod;

    ll h2 = rev[l];
    if (r<N-2) h2= (h2-rev[r+1])%mod;
    h2 = (h2 * bin_exp(inv, N-2-r))%mod;
    
    h1 = (h1+mod)%mod;
    h2 = (h2+mod)%mod;

    return (h1==h2);
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin>>N>>M;

    vll vl(N);
    for (int i=0; i<N; i++) cin>>vl[i];
    if (N == 1) {
        cout << 1 << '\n';
        cout << (vl[0]+vl[0])%M << '\n';
        return 0;
    }
    sort(vl.begin(), vl.end());

    set<ll> A;
    for (int i=0; i<N; i++) A.insert((vl[0]+vl[i])%M);

    vll diff(N-1);
    for (int i=0; i<N-1; i++) diff[i] = vl[i+1]-vl[i];
    ll pow=1;
    ll base = 2*M + 3;
    inv = bin_exp(base, mod-2);
    for (int i=0; i<N-1; i++) {
        if (i>0) hh[i] = hh[i-1];
        hh[i] = (hh[i] + pow*diff[i])%mod;
        pow = (pow*base)%mod;
    }

    pow=1;
    for (int i=N-2; i>=0; i--) {
        if (i<N-2) rev[i] = rev[i+1];
        rev[i] = (rev[i] + pow*diff[i])%mod;
        pow = (pow*base)%mod;
    }

    set<ll> ans;
    for (ll x: A) {
        ll idx = -1; ll dis = N;
        bool se=true;
        while (dis) {
            if (dis + idx < N && vl[dis+idx] <= x) idx+=dis;
            else dis/=2;
        }

        if (idx >= 0) {
            if (vl[idx] + vl[0] != x) se=false;
            if (!check(0, idx-1, base, N)) se=false;
        }

        idx++;
        if (idx < N) {
            if (vl[idx] + vl[N-1] != x+M) se=false;
            if (!check(idx, N-2, base, N)) se=false;
        }
        if (se) ans.insert(x);
    }

    cout << ans.size() << '\n';
    if (ans.size() == 0) return 0;
    for (ll x: ans) cout << x << ' ';
    cout << '\n';
}
