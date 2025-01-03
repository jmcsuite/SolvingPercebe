#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return (gcd(b%a, a));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n,m,N; cin>>n>>m>>N;
    ll num = m*N; 
    ll div = n;
    ll g = gcd(num, div);
    num /= g; 
    div /= g;
    ll ans = num / div;

    if ((ans * 2 + 1)*div > 2*num) cout << ans << '\n';
    else cout << ++ans << '\n';
    //cout << round(double(N*m)/double(n)) << '\n';
}
