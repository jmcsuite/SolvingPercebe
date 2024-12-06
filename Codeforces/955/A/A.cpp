#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void s() {
    ll a, b;
    ll pa, pb; 
    cin >> a >> b >> pa >> pb;
    if (a < b) {
        swap(a,b);
        swap(pa,pb);
    }

    if (pa > pb) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) s();
}
