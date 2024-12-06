#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

vll primes;

const int maxn=5e4+3;
bool crib[maxn+5];
void build() {
    for (ll i=2; i<=maxn; i++) {
        if (!crib[i]) primes.push_back(i);
        for (ll x: primes) {
            if (i*x > maxn) break;
            crib[i*x]=true;
            if (i%x == 0) break;
        }
    }
}

ll sz[maxn];
ll vl[maxn];
ll depth[maxn]; 
ll cnt[maxn];// make sure depth < N;
ll ans,t;
vll vadj[maxn];

void build(ll x, ll p){
    vl[x]=t;
    sz[x]=1;
    for (ll y : vadj[x]) {
        if (y == p) continue;
        depth[++t] = depth[vl[x]]+1;
        build(y,x);
        sz[x] += sz[y];
    }
}

void solve(ll x, ll p) {
    if (x == -1) return;

    ll big=-1; 
    for (ll y: vadj[x]) {
        if (y == p) continue;
        if (big == -1 || sz[big] < sz[y]) big=y;
    }

    // big == -1? 
    for (ll y: vadj[x]) {
        if (y == p || y == big) continue;
        solve(y,x);
        for (ll i=vl[y]; i < vl[y] + sz[y]; i++) cnt[depth[i]]--;
    }
    solve(big, x);
    for (ll y: vadj[x]) {
        if (y == p || y == big) continue;
        for (ll i=vl[y]; i < vl[y]+sz[y]; i++) {
            for (ll pr: primes) {
                ll need = pr + 2*depth[vl[x]] - depth[i];
                if (need >= 0 && need < maxn) ans += cnt[need];
            }
        }

        for (ll i=vl[y]; i < vl[y]+sz[y]; i++) cnt[depth[i]]++;
    }

    for (ll pr: primes) {
        ll need = pr + depth[vl[x]];
        if (need >= 0 && need < maxn) ans += cnt[need];
    }
    cnt[depth[vl[x]]]++;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    build();
    ll N; cin>>N;
    for (int i=1; i<N; i++) {
        ll a,b; cin >> a >> b;
        --a; --b;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
    }
    build(0,0);
    solve(0,0);
    double tot = (N * (N-1) ) / 2;
    cout << fixed << setprecision(7);
    cout << ans / tot << '\n';
}
