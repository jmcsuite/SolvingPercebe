#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

const int maxn = 1e5;
using vll = vector<ll>;

vll vadj[maxn];

int main() {
    ll cc = 0;
    set<pll> st;
    ll N,R; cin>>N>>R;
    for (int i=0; i<N; i++) {
        ll x; cin >> x;
        if (st.empty() || st.begin()->first + R >= x) {
            vadj[cc].push_back(i);
            st.insert({x,cc++});
        }
        else {
            vadj[st.begin()->second].push_back(i);
            st.insert({x,st.begin()->second});
            st.erase(st.begin());
        }
    }
    cout << cc << '\n';
    for (int i=0; i<cc; i++) {
        cout << vadj[i].size();
        for (ll x: vadj[i]) cout << ' ' << x+1;
        cout << '\n';
    }
}
