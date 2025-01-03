#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) {
    if (a==0) return b;
    if (b==0) return a;
    return gcd(b%a, a);
}

ll pp(ll a, ll x) {
    ll ans = 1;
    for (int i=0; i<x; i++) ans *= a;
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll A,B,C; cin>>A>>B>>C;
    ll G = gcd(A,B);
    ll K = ((C-1)*G) / (B*A);

    ll X = pp(2,(B/G)*K);
    ll Y = pp(2,(A/G)*K);
    ll Z = 2;

    cout << X << '\n' << Y << '\n' << Z << '\n';
}
