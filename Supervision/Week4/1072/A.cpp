#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

map<ll,ll> pr;
map<ll, vll> vadj;

ll toint(string x) {
    stringstream xx(x);
    ll ans = 0;
    for (string p; getline(xx, p, '.');) {
        ans *= 256ll;
        ans += stoi(p);
    }
    return ans;
}

void bfs(ll b) {
    pr[b] = b;
    queue<ll> q; q.push(b);
    while (!q.empty()) {
        ll x = q.front(); q.pop();
        auto vec = vadj[x];
        for (ll y: vec) {
            if (pr.find(y) != pr.end()) continue;
            pr[y] = x;
            q.push(y);
        }
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    for (int i=0; i<N; i++) {
        ll M; cin>>M;
        for (int j=0; j<M; j++) {
            string a,b; cin>>a>>b;
            ll aa,bb; aa = toint(a);
            bb = toint(b);
            aa &= bb;

            aa += N + 3;
            vadj[i].push_back(aa);
            vadj[aa].push_back(i);
        }
    }

    ll a,b; cin >> a >> b; --a; --b;
    bfs(a);
    if (pr.find(b) == pr.end()) {
        cout << "No\n"; 
        return 0;
    }
    cout << "Yes\n";

    ll x = b; 
    vll ans;
    while (pr[x] != x) {
        ans.push_back(x); 
        x = pr[x];
    }
    reverse(ans.begin(), ans.end());

    cout << ++x;
    for (int i=1; i < (int)ans.size(); i+=2) cout << ' ' << ++ans[i];
    cout << '\n';
}
