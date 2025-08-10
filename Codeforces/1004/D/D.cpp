#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll,ll>;
const int maxn = 2e5+2;
ll vl[maxn];
bool se[maxn];

ll query(ll i, ll j) {
    cout << "? " << i << ' ' << j << endl;
    ll x; cin>>x;
    return x;
}

void ss(char x) {
    cout << "! " << x << endl;
}
ll n;
void sol_no_perm() {
    ll a;
    for (int i=1; i<=n; i++) {
        if (se[i] == false) a = i;
    }
    ll b = 1;
    if (b == a) b++;
    ll x = query(a,b);
    if (x == 0) ss('A');
    else ss('B');
}

void solve() {
    cin>>n;
    for (int i=0; i<n; i++) cin>>vl[i];
    for (int i=1; i<=n; i++) se[i]=false;
    for (int i=0; i<n; i++) se[vl[i]]=true;

    for (int i=1; i<=n; i++) {
        if (se[i] == false) {
            sol_no_perm();
            return;
        }
    }
    
    ll a,b; 
    for (int i=0; i<n; i++) if (vl[i] == 1) a=i;
    for (int i=0; i<n; i++) if (vl[i] == n) b=i;
    ll x1 = query(a+1,b+1);
    ll x2 = query(b+1,a+1);

    if (x1 < n-1) {
        ss('A');
        return;
    }
    if (x1 > n-1) {
        ss('B');
        return;
    }

    if (x2 == n-1) ss('B');
    else ss('A');
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while (t--) solve();
}
