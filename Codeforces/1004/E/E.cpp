#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int maxn = 2e5;
ll v[maxn];

bool sol(vll& vl) {
    ll n = vl.size();
    vll mex(n);
    set<ll> st; 

    for (int i=0; i<=n; i++) st.insert(i);
    for (int i=n-1; i>=0; i--) {
        st.erase(vl[i]);
        mex[i] = *st.begin();
    }
    ll mini = vl[0];
    for (int i=0; i<n-1; i++) {
        mini = min(mini,vl[i]);
        if (mini < mex[i+1]) return false;
    }
    return true;
}


void solve() {
    ll n; cin>>n;
    for (int i=0; i<n; i++) cin>>v[i];
    bool se = false;
    vll vl;
    for (int i=0; i<n; i++)  {
        if (v[i] != 0) vl.push_back(v[i]);
        else if (!se) vl.push_back(v[i]);
        if (v[i] == 0) se = true;
    }
    if (sol(vl)) cout << vl.size() << '\n';
    else cout << int(vl.size()) - 1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while (t--) solve();
}
