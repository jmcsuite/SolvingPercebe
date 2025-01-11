#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=2e5;
ll vl[maxn];
ll n;

ll calc(ll i, ll j) {
    ll a = i;
    ll ans = 1;
    for (int k=i+1; k<n; k++) {
        if (vl[k] - vl[a] != vl[j] - vl[i]) continue;
        ans++;
        a = k;
    }
    a = i;
    for (int k=i-1; k>=0; k--) {
        if (vl[a] - vl[k] != vl[j] - vl[i]) continue;
        ans++;
        a = k;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll k; cin>>n>>k;
    for (int i=0; i<n; i++) cin>>vl[i];
    ll x, ans; 
    ans = 0;
    for (int i=0; i<k+1; i++) {
        ll s = calc(i*2, i*2 + 1);
        if (s <= ans) continue;
        x = i*2;
        ans = s;
    }

    if (ans + k < n) {
        cout << -1 << '\n';
        return 0;
    }

    vll sol;
    ll a = x;
    for (int l=x+1; l<n; l++) {
        if (vl[l] - vl[a] == vl[x+1] - vl[x]) {
            a = l;
            continue;
        }
        sol.push_back(l);
    }

    a = x;
    for (int l=x-1; l>=0; l--) {
        if (vl[a] - vl[l] == vl[x+1] - vl[x]) {
            a = l;
            continue;
        }
        sol.push_back(l);
    }
    sort(sol.begin(), sol.end());
    cout << sol.size() << '\n';
    for (size_t i=0; i<sol.size(); i++) cout << ++sol[i] << (i+1 == sol.size() ? '\n' : ' ');
}
    

