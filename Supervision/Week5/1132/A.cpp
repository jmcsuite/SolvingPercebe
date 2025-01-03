#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;


const int maxn=32768;
const int maxc=3515;
const int maxq=1e5;

pair<pll,ll> q[maxq];
ll ans[maxn];
void build(ll p) {
    for (int i=0; i<=p; i++) ans[i]=0;
    for (int i=1; i<=p/2; i++) ans[(i*i)%p]=i;
}

ll sol[maxq];
ll pp[maxq];


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll Q; cin>>Q; 
    for (int i=0; i<Q; i++) {
        q[i].second = i;
        cin >> q[i].first.second >> q[i].first.first;
    }
    sort(q, q+Q);
    for (int i=0; i<Q; i++) {
        if (i == 0 || q[i].first.first != q[i-1].first.first) build(q[i].first.first);
        q[i].first.second %= q[i].first.first;
        sol[q[i].second] = ans[q[i].first.second];
        pp[q[i].second] = q[i].first.first;
    }
    
    for (int i=0; i<Q; i++) {
        if (sol[i] == 0) {
            cout << "No root\n";
            continue;
        }

        cout << sol[i];
        if (pp[i] - sol[i] != sol[i]) cout << ' ' << pp[i]-sol[i] << '\n';
        else cout << '\n';
    }
}
