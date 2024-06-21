#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxm = 316;
const int maxn = 1e5;

vector<ll> vadj[maxn];
vector<ll> vadj_big[maxn];

ll soy[maxn];
ll me[maxn];

ll vl[maxn];

void q(ll i, ll x) {
    soy[i] += x;
    if (vadj[i].size() <= maxm) {
        for (auto y : vadj[i]) me[y] += x;
        return;
    }
    for (auto y : vadj_big[i]) me[y] += x;
}

ll sol(ll i) {
    ll ans = soy[i];
    if (vadj[i].size() <= maxm) {
        for (auto y : vadj[i]) ans += soy[y];
        return ans;
    }
    return ans + me[i];
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M, Q;
    cin >> N >> M >> Q;
    for (int i = 0; i < N; i++) cin >> vl[i];
    for (int i = 0; i < N; i++) {
        ll a; cin >> a;
        vl[i] -= a;
    }
    for (int i = 0; i < M; i++) {
        ll a,b; cin >> a >> b; a--; b--;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
    }

    for (int i = 0; i < N; i++) {
        if(vadj[i].size() <= maxm) continue;
        for (auto y : vadj[i]) vadj_big[i].push_back(y);
    }

    for (int i = 0; i < N; i++) q(i, vl[i]);
    while (Q--) {
        string a; cin >> a;
        if (a == "check") {
            ll x; cin >> x; x--;
            ll ans = sol(x);
            if (ans > 0) {
                cout << "desks\n";
            } else if (ans < 0) {
                cout << "monitors\n";
            } else {
                cout << "same\n";
            }
            continue;
        }
        string t;
        ll c, x; cin >> c >> t >> x;
        x--;
        if (t == "monitor") c *= -1;
        q(x,c);
    }
}
