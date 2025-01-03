#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 1e4;
ll t[maxn];
ll d[maxn];
vll vadj[maxn];

struct frac {
    ll x,y;
    frac() : x(1), y(1) {}
    frac(ll a, ll b) : x(a), y(b) {}
    bool operator<(const frac& other) const {
        return (x * other.y) < (other.x * y);
    }
};

frac v; 
void calc(ll x) {
    d[x] = t[x];
    if (vadj[x].empty()) return;
    vll s; 
    for (ll y: vadj[x]) {
        calc(y);
        s.push_back(d[y]);
    }
    sort(s.begin(), s.end());
    ll pos = (v.x*ll(vadj[x].size()) + v.y - 1) / v.y;
    if (pos == 0) return;
    d[x] += s[pos-1];
}

ll tt(frac x) {
    v = x;
    calc(0);
    return d[0];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,T; cin>>N>>T;
    for (int i=1; i<N; i++) {
        ll x; cin>>x>>t[i];
        --x;
        vadj[x].push_back(i);
    }

    vector<frac> vl;
    for (int i=0; i<N; i++) {
        if (vadj[i].size() == 0) continue;
        ll M = vadj[i].size();
        for (int j=1; j < M; j++) vl.push_back({j,M});
    }
    vl.push_back({0,1});
    vl.push_back({1,1});
    sort(vl.begin(), vl.end());

    ll ans = 0; 
    ll dis = vl.size() - 1;
    while (dis) {
        if (ans+dis < ll(vl.size()) && tt(vl[ans+dis]) <= T) ans+=dis;
        else dis/=2;
    }
    double pp = double(vl[ans].x) / double(vl[ans].y);
    pp *= 100;
    cout << fixed << setprecision(6);
    cout << pp << '\n';
}
