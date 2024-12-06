#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        vll vl(3); cin >> vl[0] >> vl[1] >> vl[2];
        sort(vl.begin(), vl.end());
        cout << vl[2] - vl[0] << '\n';
    }
}
