#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int maxn = 2e5;

ll vl[maxn];
ll ans[maxn];
ll pr[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N, C; cin >> N >> C;
        for (int i = 0; i < N; i++) cin >> vl[i];
        vl[0] += C;
        pr[0] = vl[0];
        for (int i = 1; i < N; i++) pr[i] = vl[i] + pr[i-1];
        ll maxi = 0;
        ll id = 0;
        for (int i = 0; i < N; i++) maxi = max(maxi, vl[i]);
        for (int i = 0; i < N; i++) {
            if (vl[i] == maxi) {
                id = i;
                break;
            }
        }

        for (int i = 0; i < N; i++) {
            if (vl[i] > maxi || (vl[i] == maxi && id == i)) {
                ans[i] = 0; 
                continue;
            }
            if (i > 0) vl[i] += pr[i-1];
            if (vl[i] >= maxi) {
                ans[i] = i;
                continue;
            }
            ans[i] = i + 1;
        }
        for (int i = 0; i < N; i++) cout << ans[i] << (i == N-1 ? '\n' : ' ');
    }
}
