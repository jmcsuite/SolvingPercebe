#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

const int maxn = 2*1e6+1;

ll crib[maxn];
ll p[maxn];
ll vis[maxn];
ll vl[maxn];
ll org[maxn];
pll last[maxn];

void cr() {
    for (ll i = 2; i < maxn; i++) {
        if (crib[i]) continue;
        for (ll j = 1; j*i < maxn; j++) crib[i*j] = i;
    }
}

void clear(ll N) {
    for (int i = 0; i < N; i++) p[i] = i;
    for (int i = 0; i < N; i++) vis[i] = 0;
}

ll f(ll x) {
    return (p[x] == x ? x : p[x] = f(p[x]));
}

void un(ll a, ll b) {
    ll pa = f(a);
    ll pb = f(b);

    p[pb] = pa;
}

ll TC = 0;
ll pp = 0;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cr();
    for (int i = 0; i < maxn; i++) last[i] = {-1, -1};
    ll T; cin >> T;
    while (T--) {
        TC++;
        ll N, K; cin >> N >> K;
        if (TC == 1) pp = N;
        clear(2*N); ll ans = 0;
        for (int i = N; i < 2*N; i++) cin >> vl[i];
        for (int i = 0; i < N; i++) org[i] = vl[i+N];
        for (int i = N; i < 2*N; i++) {
            if (vl[i] == 1) {
                ans += N; 
                vl[i] = 0;
            }
        }

        for (int i = 0; i < N; i++) vl[i] = vl[i+N];
        /*
        for (int i = 0; i < N; i++) cin >> vl[i]; //read
        for (int i = 0; i < N; i++) vl[i+N] = vl[i]; //duplicate

        for (int i = N; i < 2*N; i++) if (vl[i] == 1) vl[i] = 0; //remove 1s
        for (int i = 0; i < N; i++) { // remove 1s
            if (vl[i] > 1) continue;
            vl[i] = 0;
            ans += N;
        }
        */

        for (int i = 1; i < 2*N; i++) {
            while (vl[i] > 1) {
                ll primo = crib[vl[i]];
                vl[i] /= primo;
                if (last[primo].first == T && last[primo].second + K >= i) un(last[primo].second, i);
                last[primo] = {T, i};
            }
        }

        for (int i = 1; i < 2*N; i++) {
            if (vl[i] == 0) continue;
            ll pi = f(i); 
            if (vis[pi]) continue;
            ans++; vis[pi] = 1;
        }
        cout << ans << '\n';
        /*if (TC == 26 && ans == 1 && pp == 26) {
            cout << N << ' ' << K << endl;
            for (int i = 0; i < N; i++) cout << org[i] << ' ';
            cout << endl;
        }*/
    }
}
