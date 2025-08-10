#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

ll press(char c) {
    if (c == 'R') return 0;
    if (c == 'G') return 2;
    if (c == 'B') return 1;
    return 0;
}


ll need(ll button_press, ll pneed) {
    ll x = pneed - button_press;
    while (x<0) x+=3;
    if (x >= 3) {
        while (1) x++;
    }
    return x;
}

const int maxb  = 4e5;
const int maxn = 2e5;
ll vis[maxb];
vector<pll> vadj[maxb];
vector<ll> vv[maxn];
ll vl[maxn];

void setup() {
    for (int i=0; i<maxb; i++) vis[i] = -1;
}
ll ans = 0;
ll cc = 0;
bool pos = true;

void mark(ll x) {
    if (vis[x] != -1) return;
    vis[x] = 0;
    for (pll p: vadj[x]) mark(p.first);
}


list<ll> q;
void algo(ll x, ll s) {
    if (vis[x] != -1 && vis[x] == s) return;
    if (vis[x] != -1) {
        pos = false;
        return;
    }
    vis[x] = s;
    cc += s;
    for (pll p: vadj[x]) {
        algo(p.first, need(s,p.second));
    }
    q.push_back(x);
}

const string impossible = "impossible";
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    setup();

    ll y,z; cin>>y>>z;
    for (int i=0; i<y; i++) {
        char c; cin>>c;
        vl[i] = press(c);
    }

    for (int i=0; i<z; i++) {
        ll k; cin>>k;
        for (int j=0; j<k; j++) {
            ll x; cin>>x;
            --x;
            vv[x].push_back(i);
        }
    }

    map<pll,ll> mp;
    for (int i=0; i<y; i++) {
        if (vv[i].empty()) {
            if (vl[i] != 0) {
                cout << impossible << '\n';
                return 0;
            }
            continue;
        }
        if (vv[i].size() == 1) {
            ll x = vv[i][0];
            if (vis[x] != -1 && vis[x] != vl[i]) {
                cout << impossible << '\n';
                return 0;
            }
            if (vis[x] == -1) ans += vl[i];
            vis[x] = vl[i];
            continue;
        }

        if (vv[i].size() > 2) {
            cout << impossible << '\n';
            return 0;
        }

        ll a,b; 
        a = vv[i][0];
        b = vv[i][1];

        ll mini = min(a,b);
        ll maxi = max(a,b);

        auto it = mp.find({mini,maxi});
        if (it == mp.end()) {
            vadj[a].push_back({b,vl[i]});
            vadj[b].push_back({a,vl[i]});
            mp[{mini,maxi}] = vl[i];
            continue;
        }
        if (it->second != vl[i]) {
            cout << impossible << '\n';
            return 0;
        }
    }


    for (int i=0; i<z; i++) {
        if (vis[i] != -1) continue;
        ll mincc = maxb * 3;
        for (int k=0; k<3; k++) {
            cc = 0;
            pos = true;
            algo(i, k);

            if (pos) mincc = min(mincc, cc);
            for (ll x : q) vis[x] = -1;
            q.clear();
        }
        if (mincc == maxb * 3) {
            cout << impossible << '\n';
            return 0;
        }
        mark(i);
        ans += mincc;
    }
    cout << ans << '\n';
}
