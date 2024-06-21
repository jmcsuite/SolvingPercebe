#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

string a,b;
pll get_range(ll i) {
    if (a[i] == '1') return {i, i};
    if (i > 0 && i+1 < (int)a.size() && b[i-1] == '1' && b[i+1] == '1') return {i-1, i+1};
    if (i > 1 && i+1 < (int)a.size() && a[i-2] == '0' && b[i+1] == '1') return {i-2, i+1};
    if (i > 0 && i+2 < (int)a.size() && b[i-1] == '1' && a[i+2] == '0') return {i-1, i+2};
    if (i > 1 && i+2 < (int)a.size() && a[i-2] == '0' && a[i+2] == '0') return {i-2, i+2};
    return {-1, -1};
}

const int maxn = 2e5;
ll cum[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N >> a >> b;
        for (int i = 0; i < N; i++) {
            pll x = get_range(i); 
            cum[i] = (x.first == -1 ? 0 : 1);
        }
        for (int i = 1; i < N; i++) cum[i] = cum[i] + cum[i-1];
        ll Q; cin >> Q;
        while (Q--) {
            ll l, r; cin >> l >> r; l--; r--;

            ll lr = l+2; ll rl = r-2;
            ll sum = 0;
            if (lr <= rl) sum = cum[rl] - cum[lr-1];
            if (lr <= rl) {
                for (int i = l; i < lr; i++) {
                    pll x = get_range(i); 
                    if (x.first >= l && x.second <= r) sum++;
                }
                for (int i = rl+1; i <= r; i++) {
                    pll x = get_range(i); 
                    if (x.first >= l && x.second <= r) sum++;
                }
            }
            else {
                for (int i = l; i <= r; i++) {
                    pll x = get_range(i); 
                    if (x.first >= l && x.second <= r) sum++;
                }
            }
            cout << sum << '\n';
        }
    }
}
