#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll a,b,c;
    while(cin>>c>>a>>b) {
        ll i = a; ll d = a; ll sz = 1;
        for (int k = 1; k <= c; k++) {
            if ((d+sz) % (2*sz)) i -= sz;
            else d += sz;
            sz *= 2;
            if (b >= i && b <= d) {
                cout << k << '\n';
                break;
            }
        }
    }
}
