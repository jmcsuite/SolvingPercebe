#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+1;
const int maxr = 317;
const int mod = 1e9 + 7;

using pll = pair<ll,ll>;
using vll = vector<ll>;
vll vadj[maxn];
vll bigadj[maxn];
ll vl[maxn];
ll prop[maxn];
pll edge[maxn];

ll getvaluesmall(ll x) {
    ll v = vl[x];
    //for (ll y: bigadj[x]) v = (v + prop[y]) % mod;
    for (ll y: bigadj[x]) v += prop[y];
    return v%mod;
}

ll getvaluebig(ll x) {
    return vl[x]%mod;
}

void updatesmall(ll x) {
    ll v = getvaluesmall(x);
    //for (ll y: vadj[x]) vl[y] = (vl[y] + v)%mod;
    for (ll y: vadj[x]) vl[y] += v;
}

void updatebig(ll x) {
    //prop[x] = (prop[x] + vl[x]) % mod;
    prop[x] += vl[x];
    //for (ll y: bigadj[x]) vl[y] = (vl[y] + vl[x])%mod;
    for (ll y: bigadj[x]) vl[y] += vl[x];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    for (int i=1; i<=N; i++) cin>>vl[i];
    for (int i=1; i<N; i++) {
        cin >> edge[i].first >> edge[i].second;
        vadj[edge[i].first].push_back(edge[i].second);
        vadj[edge[i].second].push_back(edge[i].first);
    }

    for (int i=1; i<N; i++) {
        if (vadj[edge[i].first].size() >= maxr) bigadj[edge[i].second].push_back(edge[i].first);
        if (vadj[edge[i].second].size() >= maxr) bigadj[edge[i].first].push_back(edge[i].second);
    }

    ll Q; cin>>Q;
    while (Q--) {
        ll q,x; cin>>q>>x;
        if (q == 2) {
            if (vadj[x].size() >= maxr) cout << getvaluebig(x) << '\n';
            else cout << getvaluesmall(x) << '\n';
            continue;
        }

        if (vadj[x].size() >= maxr) updatebig(x);
        else updatesmall(x);
    }
}
