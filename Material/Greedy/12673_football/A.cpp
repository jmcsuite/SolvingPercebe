#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, G;
    while (cin >> N >> G) {
        ll ans = 0;
        vll vl;
        for (int i = 0; i < N; i++) {
            ll a, b; cin >> a >> b;
            if (a > b) {
                ans+=3;
                continue;
            }
            vl.push_back(b-a);
        }
        sort(vl.begin(), vl.end());

        ll c = 0;
        while (c < (int)vl.size() && G) {
            if (vl[c] >= G) {
                vl[c] -= G;
                break;
            }
            else {
                G -= (vl[c]+1);
                c++; 
            }
        }
        for (int i = c; i < (int)vl.size(); i++) {
            if (vl[i] == 0) ans++;
        }
        cout << ans + c*3 << '\n';
    }
}
