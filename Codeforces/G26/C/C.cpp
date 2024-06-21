#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5;
const long long mod = 998244353;
ll vl[maxn];
ll s[maxn];
ll m[maxn];
ll p[maxn];


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        for (int i = 0; i < N; i++) cin >> vl[i];
        s[0] = vl[0]; 
        for (int i = 1; i < N; i++) s[i] = vl[i] + s[i-1];
        m[N-1] = s[N-1];
        for (int i = N-2; i >= 0; i--) m[i] = min(s[i], m[i+1]);
        p[N-1] = 2;
        for (int i = N-2; i >= 0; i--) p[i] = (2ll * p[i+1]) % mod;


        ll paths = 1;
        ll ans = 0; 
        ll c = 0;
        for (int i = 0; i < N; i++) {
            ll c1 = c + vl[i];
            ll c2 = c + vl[i]; if (c2 < 0) c2*=-1;
            if (c1 == c2) {
                c = c1;
                paths = (paths * 2) % mod;
                continue;
            }
            if (i == N-1) {
                c = c2; 
                continue;
            }

            ll mt = m[i+1] - s[i];
            if (mt < 0) {
                c = c1; 
                continue;
            } else if (mt > 0) {
                c = c2;
                continue;
            }
            else {
                c = c1;
                ans = (ans + paths * p[i+1])%mod;
            }
        }
        ans = (ans + paths) % mod;
        cout << ans << '\n';
    }
}
