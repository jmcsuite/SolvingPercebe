#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

vll primes;

const int maxn=5e4;
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

ll ans;
vll nums[maxn+5];
map<ll,ll> P[maxn+5];
ll sz[maxn+5];

ll depth[maxn+5];

void add(const long long x, const long long a) {
    if (P[x].size() < P[a].size()) {
        //swap(sz[x], sz[a]);
        swap(P[x], P[a]);
        //swap(nums[x], nums[a]);
    }

    //sz[x] += sz[a];
    /*
    for (ll u : nums[a]) {
        auto it = P[x].find(u-2*depth[x]);
        if (it == P[x].end()) continue;
        ans += it->second;
    }*/
    
    for (ll p : primes) {
        p += 2*depth[x];
        for (pll pp : P[a]) ans = ans + pp.second * P[x][p-pp.first];
    }

    for (pll p: P[a]) P[x][p.first] += p.second;
    //for (ll u: nums[a]) nums[x].push_back(u);
    //nums[a].clear();
    P[a].clear();
}

vll vadj[maxn+5];
void DFS(const long long x, const long long p) {
    depth[x] = depth[p] + 1;
    //sz[x] = 1;
    //nums[x].push_back(depth[x]);
    
    P[x][depth[x]]++;
    for (ll y: vadj[x]) {
        if (y == p) continue;
        DFS(y,x);
        add(x, y);
    }
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
    DFS(0,0);
    double tot = (N * (N-1) ) / 2;
    cout << fixed << setprecision(7);
    cout << ans / tot << '\n';
}
