#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<ll>;
using vpll = vector<pll>;

const int base = 28;
const long long m2 = 999999391;
const long long m1 = 999999193;
const int maxn = 2e5 + 5;

ll pm1[maxn];
ll pm2[maxn];

void pre() {
    pm1[0] = pm2[0] = 1;
    for (int i=1; i<maxn; i++) pm1[i] = (pm1[i-1]*base)%m1;
    for (int i=1; i<maxn; i++) pm2[i] = (pm2[i-1]*base)%m2;
}

namespace trie{
ll n = 1;
ll vadj[maxn][base];
ll cc[maxn];
ll depth[maxn];
ll pref[maxn];
ll hash[maxn];
ll dos[maxn];
map<pll,ll> mp;

void add(string s) {
    ll x = 0;
    for (char d: s) {
        int c = d-'a'+1;
        if (vadj[x][c] == 0) vadj[x][c] = n++;
        depth[vadj[x][c]] = depth[x]+1;
        hash[vadj[x][c]] = (hash[x] + c*pm1[depth[x]])%m1;
        dos[vadj[x][c]] = (dos[x] + c*pm2[depth[x]])%m2;
        x = vadj[x][c];
        cc[x]++;
    }
}

void pre() {
    for (int i=0; i<n; i++) {
        mp[{hash[i],dos[i]}] = i;
        pref[i] += cc[i];
        for (int j=0; j<base; j++) {
            if (vadj[i][j] == 0) continue;
            pref[vadj[i][j]] += pref[i];
        }
    }
}
}

vpll vadj[maxn];

void solve() {
    ll n; cin>>n;
    vector<ll> vl(n);
    for (int i=0; i<n; i++) cin>>vl[i];
    for (int i=0; i<n; i++) vl[i]--;
    pll h(0,0);
    ll d=0;
    int i=0;
    for (; i<n; i++) {
        ll nh1 = (h.first + vadj[vl[i]].back().first * pm1[d])%m1;
        ll nh2 = (h.second + vadj[vl[i]].back().second * pm2[d])%m2;
        pll nh(nh1,nh2);
        if (trie::mp.find(nh) == trie::mp.end()) break;
        h = nh;
        d += vadj[vl[i]].size();
    }
    if (i == n) {
        cout << trie::pref[trie::mp[h]] << '\n';
        return;
    }

    i = vl[i];
    ll dis = vadj[i].size() + 1;
    ll ans = -1;
    while (dis) {
        if (ans + dis >= (int)vadj[i].size()) {
            dis/=2;
            continue;
        }
        ll nh1 = (h.first + vadj[i][ans+dis].first*pm1[d])%m1;
        ll nh2 = (h.second + vadj[i][ans+dis].second*pm2[d])%m2;
        pll nh(nh1,nh2);
        if (trie::mp.find(nh) != trie::mp.end()) ans+=dis;
        else dis/=2;
    }
    pll nh;
    if (ans >= 0) {
        ll nh1 = (h.first + vadj[i][ans].first*pm1[d])%m1;
        ll nh2 = (h.second + vadj[i][ans].second*pm2[d])%m2;
        nh.first = nh1;
        nh.second = nh2;
    }
    else {
        nh = h;
    }
    cout << trie::pref[trie::mp[nh]] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    pre();
    ll n; cin>>n;
    for (int i=0; i<n; i++) {
        string x; cin>>x;
        trie::add(x);
    }
    trie::pre();

    cin>>n;
    for (int i=0; i<n; i++) {
        string x; cin>>x;
        vadj[i].resize(x.size());
        for (int j=0; j<(int)x.size(); j++) {
            ll c = x[j] - 'a' + 1;
            ll h = (c * pm1[j])%m1;
            if (j > 0) h = (h + vadj[i][j-1].first) % m1;
            vadj[i][j].first = h;

            h = (c*pm2[j])%m2;
            if (j > 0) h = (h + vadj[i][j-1].second) % m2;
            vadj[i][j].second = h;
        }
    }
    ll q; cin>>q;
    while (q--) solve();
}
