#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxp = 1e6+1;

ll crib[maxp];
vector<ll> vadj[maxp];

void build() {
    for (ll i = 2; i < maxp; i++) {
        if (crib[i]) continue;
        crib[i] = i;
        for (ll j = i; j*i < maxp; j++) {
            if (crib[i*j]) continue;
            crib[i*j] = i;
        }
    }
}


const int maxn = 1e5;
ll N;
ll vl[maxn];

void desc() {
    for (int i = 0; i < N; i++) {
        while (vl[i] != 1) {
            vadj[crib[vl[i]]].push_back(i);
            vl[i] /= crib[vl[i]];
        }
    }
}

// [l, r]
bool f(ll x, ll c, ll l, ll r) {
    ll der = -1;
    ll inc = N;
    while(inc) {
        if (der + inc < (int)vadj[x].size() && vadj[x][der+inc] <= r) der+=inc;
        else inc/=2;
    }

    ll izq = vadj[x].size(); 
    inc = N;
    while(inc) {
        if (izq - inc >= 0 && vadj[x][izq-inc] >= l) izq-=inc;
        else inc/=2;
    }
    ll dis = der - izq + 1;
    if (dis >= c) return true;
    return false;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) cin >> vl[i];
    build();
    desc();
    ll Q; cin >> Q;
    while (Q--) {
        ll l, r, x;
        cin >> l >> r >> x;
        l--; r--;
        bool ans = true;
        while (x != 1) {
            ll pr = crib[x];
            ll cc = 0;
            while (crib[x] == pr) {
                x /= pr;
                cc++;
            }
            ans &= f(pr, cc, l, r);
        }
        cout << (ans ? "Yes\n" : "No\n");
    }
}
