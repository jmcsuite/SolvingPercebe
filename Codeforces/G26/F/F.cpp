#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e3 + 2;

const long long mod = 998244353;
ll ps = 0;
ll N, M;

ll dp[2][maxn];
ll b[maxn];
ll s[maxn];

const int S = 1;
const int P = 0;
const int NO = 2;

ll F(ll i, ll p) {
    if (i == N-1) return 1;
    if (dp[p][i] != -1) return dp[p][i];

    ll ans = 0;
    if (p == P) { // P
        if (s[i+1] == S && b[i] + b[i+1] == ps) ans = (ans + F(i+1, S))%mod;
        if (s[i+1] == NO && b[i] + b[i+1] == ps) ans = (ans + F(i+1, S))%mod;
        if (s[i+1] == P || s[i+1] == NO) {
            if ((b[i+1] - b[i]) <= M && (b[i] - b[i+1]) <= M) ans = (ans + F(i+1, P))%mod;
        }
    }
    else {
        if (s[i+1] == S || s[i+1] == NO) {
            if ((b[i] - b[i+1]) <= M && (b[i+1] - b[i]) <= M) ans = (ans + F(i+1, S))%mod;
        }
        if (s[i+1] == P || s[i+1] == NO) {
            ll d = b[i] + b[i+1] - ps;
            if (d < 0) d *= -1;
            ll a = d - d/2;
            if (a <= M) ans = (ans + F(i+1, P))%mod;
        }
    }
    return dp[p][i] = ans;
}


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        cin >> N >> M; 
        string ss; cin >> ss;
        for (int i = 1; i <= N; i++) cin >> b[i];
        b[0] = 0; b[N+1] = 0;
        ss = "P" + ss + "S";
        N += 2;
        for (int i = 0; i < N; i++) {
            if (ss[i] == 'P') s[i] = P;
            else if (ss[i] == 'S') s[i] = S;
            else s[i] = NO;
        }

        set<ll> st;
        ll ans = 0;
        for (int i = 0; i < N-1; i++) {
            ps = b[i] + b[i+1];
            if (st.find(ps) != st.end()) continue;
            st.insert(ps);
            memset(dp, -1, sizeof(dp));
            ans = (ans + F(0, P)) % mod;
            // cout << ps << ' ' << ans << endl;
        }
        cout << ans << '\n';
    }
}
