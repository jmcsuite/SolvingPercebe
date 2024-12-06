#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<ll>;

const int m1 = 999999391;
const int m2 = 999999323;

const int maxn = 3e5;
ll p1[maxn];
ll p2[maxn];

void fill() {
    p1[0] = p2[0] = 1;
    for (int i = 1; i < maxn; i++) p1[i] = (p1[i-1] * 2) % m1;
    for (int i = 1; i < maxn; i++) p2[i] = (p2[i-1] * 2) % m2;
}



void solve() {
    ll N, M; cin >> N >> M;
    vector<vll> vadj(N, vll(M));

    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        for (int j = 0; j < M; j++) vadj[i][j] = (s[j] == '1' ? 1 : 0);
    }

    map<pll, ll> mp;
    for (int j = 0; j < M; j++) {
        ll h1, h2; 
        h1 = h2 = 0;

        for (int i = 0; i < N; i++) {
            h1 = (h1 + vadj[i][j]*p1[i]) % m1;
            h2 = (h2 + vadj[i][j]*p2[i]) % m2;
        }

        for (int i = 0; i < N; i++) {
            if (vadj[i][j] == 0) {
                ll n_h1 = (h1 + p1[i]) % m1;
                ll n_h2 = (h2 + p2[i]) % m2;
                mp[{n_h1, n_h2}]++;
            }
            else {
                ll n_h1 = (h1 - p1[i]) % m1;
                ll n_h2 = (h2 - p2[i]) % m2;
                n_h1 = (n_h1 + m1) % m1;
                n_h2 = (n_h2 + m2) % m2;
                mp[{n_h1, n_h2}]++;
            }
        }
    }


    ll ans = 0; pll h;
    for(auto it : mp) {
        ans = max(ans, it.second);
        if (it.second == ans) h = it.first;
    }

    cout << ans << '\n';
    for (int j = 0; j < M; j++) {
        ll h1, h2; 
        h1 = h2 = 0;

        for (int i = 0; i < N; i++) {
            h1 = (h1 + vadj[i][j]*p1[i]) % m1;
            h2 = (h2 + vadj[i][j]*p2[i]) % m2;
        }

        for (int i = 0; i < N; i++) {
            ll n_h1, n_h2;
            if (vadj[i][j] == 0) {
                n_h1 = (h1 + p1[i]) % m1;
                n_h2 = (h2 + p2[i]) % m2;
            }
            else {
                n_h1 = (h1 - p1[i]) % m1;
                n_h2 = (h2 - p2[i]) % m2;
                n_h1 = (n_h1 + m1) % m1;
                n_h2 = (n_h2 + m2) % m2;
            }

            if (n_h1 == h.first && n_h2 == h.second) {
                for (int k = 0; k < i; k++) cout << vadj[k][j];
                cout << (vadj[i][j] == 1 ? 0 : 1);
                for (int k = i+1; k < N; k++) cout << vadj[k][j];
                cout << '\n';
                return;
            }
        }
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fill();
    ll T; cin >> T;
    while (T--) solve();
}
