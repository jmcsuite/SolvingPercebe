#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b){
    if (a == 0) return b;
    if (b == 0) return a;
    return gcd(b%a, a);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll a, b;
        cin >> a >> b;
        cout << (a*b)/gcd(a,b) << '\n';
    }
}
