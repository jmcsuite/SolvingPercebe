#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--) {
        ll a,b; cin>>a>>b;
        if (a == b && a == 1) {
            cout << 1 << '\n';
        }
        else {
            cout << b - a << '\n';
        }
    }
}
