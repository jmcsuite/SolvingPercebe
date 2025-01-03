#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<ll>;


const int maxn = 100;
vll vadj[maxn];
string s[maxn];
ll dis[maxn];

const int extra = 6;

void daikra() {
    for (int i=1; i<maxn; i++) dis[i] = 1e9;
    set<pll> st;
    st.insert({dis[0], 0});

    while (!st.empty()) {
        pll p = *st.begin(); 
        st.erase(st.begin());
        if (p.first > dis[p.second]) continue;


        ll x = p.second;
        ll nd = dis[x] + extra + s[x].size();
        if (nd > 140) continue;
        for (ll y: vadj[x]) {
            if (dis[y] <= nd) continue;
            dis[y] = nd;
            st.insert({nd, y});
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;

    vector<vector<string>> vs(N);
    for (int i=0; i<N; i++) {
        cin>>s[i];
        ll x; cin>>x;
        vs[i].resize(x);
        for (int j=0; j<x; j++) cin>>vs[i][j];
    }

    map<string, int> mp;
    for (int i=0; i<N; i++) mp[s[i]] = i;
    
    for (int i=0; i<N; i++) {
        for (string u: vs[i]) {
            int j = mp[u];
            vadj[i].push_back(j);
        }
    }
    cin.ignore();
    string ff;
    getline(cin, ff);
    dis[0] = ff.size();
    daikra();

    for (int i=0; i<N; i++) {
        if (dis[i] > 140) continue;
        for (int x : vadj[i]) dis[x] = min(dis[x], 141ll);
    }

    vector<string> ans;
    for (int i=0; i<N; i++) {
        if (dis[i] > 141) continue;
        ans.push_back(s[i]);
    }
    cout << ans.size() << '\n';
    for (string x: ans) cout << x << '\n';
}
