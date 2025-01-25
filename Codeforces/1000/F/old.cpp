#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
const int maxn = 5000;

ll cat[maxn + 10];

const int mod = 998244353;
// bracket sequence 2*k = cat[k];
void pre() {
    cat[0] = 1;
    for (int k=1; k< maxn + 10; k++) {
        for (int i=0; i<k; i++) cat[k] = ((cat[i] * cat[k-i-1]) + cat[k])%mod;
    }
}
ll calc(ll n, vector<pll>& a) {
    ll ans = 1;
    ll sum = 0;
    stack<pll> st;
    for (pll p: a) {
        if (p.second == -1) {
            pll x = st.top();
            st.pop();
            ans = (ans * cat[(p.first - x.first - 1 - sum) / 2])%mod;
            sum = x.second;
            sum += p.first - x.first + 1;
        }
        else {
           st.push({p.first, sum});
           sum = 0;
        }
    }
    ans = (ans * cat[(n - sum)/2]) % mod;
    return ans;
}

void ss(vector<pll>& a) {
    for (int i=(int)a.size() - 1; i>0; i--) {
        if (a[i] < a[i-1]) swap(a[i], a[i-1]);
    }
}


void solve() {
    vector<pll> a;
    ll n; cin>>n;
    cout << cat[n];
    set<pair<pll,ll>> st;
    st.insert({-1,2*n},2*n});
    ll ans = cat[n];
    for (int i=0; i<n; i++) {
        ll x,y; cin>>x>>y; 
        x--; y--;
        ll ans = calc(2*n, a);
        cout << ' ' << ans;
    }
    cout << '\n';
    return;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    pre();
    ll t; cin>>t; while(t--) solve();
}
