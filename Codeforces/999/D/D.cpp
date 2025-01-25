#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e5;
ll vl[maxn];

void solve() {
    ll n,m; cin>>n>>m;
    priority_queue<ll> pq; 
    for (int i=0; i<n; i++) cin>>vl[i];
    for (int j=0; j<m; j++) {
        ll x; cin>>x;
        pq.push(x);
    }
    ll i = n-1;
    sort(vl, vl+n);
    while (i>=0 && (!pq.empty())) {
        if ((int)pq.size() > i+1) break;
        if (pq.top() == vl[i]) {
            pq.pop();
            i--;
            continue;
        }
        if (vl[i] > pq.top()) break;
        ll a = pq.top();
        ll b = a/2;
        a = a-b;
        pq.pop();
        pq.push(a);
        pq.push(b);
    }
    if (i >= 0 || (!pq.empty())) cout << "No\n";
    else cout << "Yes\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while(t--) solve();
}
