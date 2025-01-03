#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

ll N; ll c; 
const int maxn = 2e5;
vll vadj[maxn];
ll ans[maxn];

void sol(ll x, ll p) {
    bool first = true;
    c++;
    for (ll y : vadj[x]) {
        if (y == p) continue;
        if (first) ans[y] = ans[x]+1;
        else ans[y] = 2*(c+1) - ans[x]%2;
        first = false;
        sol(y,x);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while (T--) {
        c = 0; cin >> N;
        for (int i = 0; i < N; i++) vadj[i].clear();
        for (int i = 1; i < N; i++) {
            ll a,b; cin >> a >> b; --a; --b;
            vadj[a].push_back(b);
            vadj[b].push_back(a);
        }
        ans[0]=1;
        sol(0,0);
        for (int i=0; i<N; i++) cout << ans[i] << (i == N-1 ? '\n' : ' ');
    }
}
