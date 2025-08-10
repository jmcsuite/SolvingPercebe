#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 2e5;
const int maxa = 1e6+ 1;
ll freq[maxa];
ll vl[maxn];

set<pll> st;
set<ll> mult;
ll sum;
void calc() {
    if (st.size() == 1) {
        cout << "Yes\n";
        return;
    }

    if (mult.empty()) {
        cout << "No\n";
        return;
    }

    if (st.size() == 2) {
        cout << "Yes\n";
        return;
    }
    auto it = st.rbegin();
    ll xx = sum - it->first;
    if (xx >= it->first) {
        cout << "Yes\n";
        return;
    }
    --it;
    xx = xx - it->first;
    if (xx >= it->first) {
        cout << "Yes\n";
        return;
    }
    cout << "No\n";
    return;
}

ll k=0;
void add(ll x) {
    sum += x;
    freq[x]++;
    if (freq[x] == 2) mult.insert(x);
    st.emplace(x,k++);
}

void rem(ll x) {
    sum -= x;
    freq[x]--;
    if (freq[x] == 1) mult.erase(x);
    st.erase(st.lower_bound({x,0}));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n,q; cin>>n>>q;
    for (int i=0; i<n; i++) cin>>vl[i];
    for (int i=0; i<n; i++) add(vl[i]);
    calc();
    while (q--) {
        char c; ll x; cin>>c>>x;
        if (c == '+') add(x);
        else rem(x);
        calc();
    }
}
