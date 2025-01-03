#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

bool seven(ll n, ll d) {
    if (n >= 3) return true;
    ll x = d*10 + d;
    return (x%7 == 0);
}

bool five(ll n, ll d) {
    if (d == 5) return true;
    return false;
}

bool one(ll n, ll d) {
    return true;
}

ll fact(ll n) {
    ll x = 1;
    for (int i=1; i<=n; i++) x*=i;
    return x;
}

bool nine(ll n, ll d) {
    if (n >= 6) return true;
    if (d == 9) return true;
    return (((fact(n)*d) % 9) == 0);
}

bool three(ll n, ll d) {
    if (n >= 6) return true;
    return (((fact(n)*d) % 3) == 0);
}

void solve() {
    ll n, d; cin>>n>>d;
    vll ans;
    if (one(n,d)) ans.push_back(1);
    if (three(n,d)) ans.push_back(3);
    if (five(n,d)) ans.push_back(5);
    if (seven(n,d)) ans.push_back(7);
    if (nine(n,d)) ans.push_back(9);
    for (ll x: ans) {
        cout << x << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--) solve();
}
