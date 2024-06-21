#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N, a, b; 
        cin >> N >> a >> b;
        if (b < a) {
            cout << N*a << '\n';
            continue;
        }
        a = max(b-N+1, a);
        
        ll i = b-a+1;
        ll s = (b)*(b+1); s/= 2; 
        s -= ((a)*(a-1))/2;
        s += (N-i)*a;
        cout << s << '\n';
    }
}
