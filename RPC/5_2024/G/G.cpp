#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxm = 1e5;
const int maxn = 2*maxm + 1;
vector<ll> vadj[maxn];
set<pair<pll,pll>> st;
map<pll, ll> mp;
pair<pll,pll> input[maxm];
ll M;

ll ans = 3;
ll cc = 1;

void add(pll x) {
    if (mp.find(x) != mp.end()) return;
    mp[x] = cc;
    cc++;
}

void add_edge(pair<pll,pll>& x) {
    st.insert(x);
    vadj[mp[x.first]].push_back(mp[x.second]);
    vadj[mp[x.second]].push_back(mp[x.first]);
}

int vis[maxn];

void dfs(ll x, ll p) {
    if (vis[x]) {
        ans = 0;
        return;
    }
    vis[x] = cc;
    for (auto y : vadj[x]) {
        if (y == p) continue;
        dfs(y, x);
    }
}

void solve_0() {
    for (int i = 0; i < M; i++) {
        ll x = mp[input[i].first];
        if (!vis[x]) dfs(x, x);
        cc++;
    }
}


ll dx[4] = {0, 1, 0, -1};
ll dy[4] = {1, 0, -1, 0};

bool check_1(pll x) {
    pll y;
    for (int k = 0; k < 4; k++) {
        y.first = x.first + dx[k];
        y.second = x.second + dy[k];
        if (mp.find(y) == mp.end()) continue;
        if(st.find({x,y}) != st.end() || (st.find({y,x}) != st.end())) continue;
        if (vis[mp[x]] == vis[mp[y]]) return true;
    }
    return false;
}

void solve_1() {
    for (int i = 0; i < M; i++) {
        if (check_1(input[i].first)) ans = 1;
        if (check_1(input[i].second)) ans = 1;
    }
}

ll lx[4] = {1, -1, -1, 1};
ll ly[4] = {1, 1, -1, -1};

bool check_2(pll x) {
    pll y;
    for (int k = 0; k < 4; k++) {
        y.first = x.first + lx[k];
        y.second = x.second + ly[k];
        if (mp.find(y) == mp.end()) continue;
        if(st.find({x,y}) != st.end() || (st.find({y,x}) != st.end())) continue;
        if (vis[mp[x]] == vis[mp[y]]) return true;
    }
    return false;
}

void solve_2() {
    for (int i = 0; i < M; i++) {
        if (check_2(input[i].first)) ans = 2;
        if (check_2(input[i].second)) ans = 2;
    }

    for (int i = 0; i < M; i++) {
        if (input[i].first.first == input[i].second.first) {
            pair<pll,pll> p2 = input[i];
            p2.first.first--;
            p2.second.first--;
            if (st.find(p2) != st.end()) ans = 2;
            p2.first.first += 2;
            p2.second.first += 2;
            if (st.find(p2) != st.end()) ans = 2;
        }
        else {
            pair<pll,pll> p2 = input[i];
            p2.first.second--;
            p2.second.second--;
            if (st.find(p2) != st.end()) ans = 2;
            p2.second.second +=2;
            p2.first.second += 2;
            if (st.find(p2) != st.end()) ans = 2;
        }
    }
}


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> M;
    for (int i = 0; i < M; i++) cin >> input[i].first.first >> input[i].first.second >> input[i].second.first >> input[i].second.second;
    for (int i = 0; i < M; i++) {
        add(input[i].first);
        add(input[i].second);
    }

    for (int i = 0; i < M; i++) {
        if (input[i].first > input[i].second) swap(input[i].first, input[i].second);
        add_edge(input[i]);
    }

    solve_0();
    if (ans == 0) {
        cout << ans << '\n';
        return 0;
    }

    solve_1();
    if (ans == 1) {
        cout << ans << '\n';
        return 0;
    }

    solve_2();
    cout << ans << '\n';
}
