#include <bits/stdc++.h>
using namespace std;

const int maxb = 16;
const int maxn = (8<<16);
using ll = long long;
using vll = vector<ll>;

ll nn(ll i, ll b) {return (i*2 + b);}
ll notn(ll i, ll b) {
    b = (b+1)%2;
    return nn(i,b);
}

vll vadj[maxn];
const int root = 1;

void add(ll x, ll t) {
    ll n = root;
    for (ll i = 15; i >= 0; i--) {
        ll nextn = nn(n, ((x&(1ll<<i)) ? 1 : 0));
        vadj[nextn].push_back(t);
        n = nextn;
    }
}

ll search(ll x, ll l, ll r) {
    ll n = root;
    ll solution = 0;
    for (ll i = 15; i>= 0; i--) {
        ll nextn = nn(n, ((x&(1ll<<i)) ? 1 : 0));
        ll notnextn = notn(n, ((x&(1ll<<i)) ? 1 : 0));

        ll ans = -1; ll dis = vadj[nextn].size();
        while (dis) {
            if (ans + dis < (int)vadj[nextn].size() && vadj[nextn][ans+dis] <= r) ans+=dis;
            else dis/=2;
        }

        if (ans != -1 && vadj[nextn][ans+dis] >= l) {
            n = nextn;
            solution = solution | (x&(1ll<<i));
        }
        else {
            n = notnextn;
            solution = solution | (((~x)&(1ll<<i)));
        }
    }
    return solution;
}


vector<long> xorKey(vector<long long> x, vector<vector<long long>> queries) {
    for (int i=1; i<=(int)x.size(); i++) add(x[i-1], i);
    vector<long> ans;
    ll mask = (1<<16) - 1;
    for (auto q: queries) {
        ll s = mask ^ q[0];
        ll f = search(s, q[1], q[2]);
        ans.push_back(f ^ q[0]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N,Q; cin >> N >> Q;
        vll vl(N);
        vector<vll> queries(Q, vll(3));
        for (int i=0; i < N; i++) cin >> vl[i];
        for (int i=0; i < Q; i++) cin >> queries[i][0] >> queries[i][1] >> queries[i][2];
        auto ans = xorKey(vl,queries);
        for (ll x : ans) cout << x << '\n';
    }
}
