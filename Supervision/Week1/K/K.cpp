#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 1e6;

namespace LCA {
    const int maxPow = 20;
    int lifting[maxn][maxPow];
    ll depth[maxn];
    ll up[maxn];
    bool vis[maxn];
    vll vadj[maxn];

    void build(int x, int p) {
        lifting[x][0] = up[x] = p;
        depth[x] = depth[p]+1;
        for(int i=0; i<maxPow-1; i++) {
            lifting[x][i+1] = lifting[lifting[x][i]][i];
        }
        for (int y:vadj[x]) {
            if (y == p) continue;
            build(y,x);
        }
    }

    ll many(ll x) {
        if (vis[x]) return 0;
        ll n = x;
        for (int pow2 = maxPow-1; pow2>=0; pow2--) {
            if (!vis[lifting[x][pow2]]) {
                x = lifting[x][pow2];
            }
        }
        return depth[n] - depth[x] + 1;
    }

    void upd(ll x) {
        while (!vis[x]) {
            vis[x]=true;
            x = up[x];
        }
    }
}
    

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N, K; cin>>N>>K;
    K = (N - 1 - K);
    vll ans;

    for (int i=0; i<N-1; i++) {
        ll a,b; cin >> a >> b;
        a--; b--;
        LCA::vadj[a].push_back(b);
        LCA::vadj[b].push_back(a);
    }

    LCA::build(N-1, N-1);
    LCA::vis[N-1]=true;

    for (ll i = N-2; i>=0; i--) {
        ll m = LCA::many(i);
        if (m > K) ans.push_back(i);
        else {
            LCA::upd(i);
            K-=m;
        }
    }

    reverse(ans.begin(), ans.end());
    for (int i=0; i<(int)ans.size(); i++) {
        cout << ++ans[i] << (i+1 == (int)ans.size() ? '\n' : ' ');
    }
}
