#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 50;
const int mod = 1e9+7;
ll pascal[maxn+1][maxn+1];

void build() {
    for (int i=0; i<=maxn; i++) pascal[i][0] = pascal[i][i] = 1;
    for (int i=1; i<=maxn; i++) {
        for (int j=1; j<i; j++) pascal[i][j] = (pascal[i-1][j] + pascal[i-1][j-1]) % mod;
    }
}

struct state {
    ll a,b,c; 
    state() : a(0), b(0), c(0) {}
    state(ll _a, ll _b, ll _c) : a(_a), b(_b), c(_c) {}
};

ll dp[maxn+1][maxn+1][2];
ll steps[maxn+1][maxn+1][2];
bool vis[maxn+1][maxn+1][2];
bool inq[maxn+1][maxn+1][2];

ll fa;
ll fb;
ll k;

bool check(ll a, ll b) {
    if (a==0 && b==0) return false;
    return ((a*50 + b*100) <= k);
}

void solve() {
    dp[0][0][1] = steps[0][0][1] = 1;
    queue<state> q; 
    q.push({0,0,1});
    inq[0][0][1] = true;
    while (!q.empty()) {
        state s = q.front(); q.pop();
        vis[s.a][s.b][s.c] = true;

        ll a = s.a;
        ll b = s.b;
        if (s.c == 1) { 
            a = fa-s.a;
            b = fb-s.b;
        }

        for (int i=0; i<=a; i++) {
            for (int j=0; j<=b; j++) {
                if (!check(i,j)) continue;
                ll na = s.a;
                ll nb = s.b; 
                ll nc = ((s.c)+1)%2;
                if (s.c == 1) {
                    na += i;
                    nb += j;
                }
                else {
                    na -= i;
                    nb -= j;
                }
                if (vis[na][nb][nc]) continue;
                dp[na][nb][nc] += (((dp[s.a][s.b][s.c]*pascal[a][i])%mod) * pascal[b][j])%mod;
                dp[na][nb][nc] %= mod;
                if (!inq[na][nb][nc]) {
                    q.push({na,nb,nc});
                    inq[na][nb][nc]=true;
                    steps[na][nb][nc]=steps[s.a][s.b][s.c]+1;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    build();
    ll N; cin >> N >> k; 
    for (int i=0; i<N; i++) {
        ll x; cin >> x;
        if (x == 50) fa++;
        else fb++;
    }
    solve();
    --steps[fa][fb][0];
    cout << steps[fa][fb][0] << '\n';
    cout << dp[fa][fb][0] << '\n';
}
