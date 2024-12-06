#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e5;

ll a[maxn]; 
ll b[maxn];
ll c[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        for (int i = 0; i < N; i++) cin >> a[i];
        for (int i = 0; i < N; i++) cin >> b[i];
        ll M; cin >> M;
        for (int i = 0; i < M; i++) cin >> c[i];
        map<ll,ll> ne; 
        map<ll,ll> have;
        for (int i = 0; i < N; i++) have[b[i]]++;
        if (have[c[M-1]] == 0) {
            cout << "NO\n";
            continue;
        }
        for (int i = 0; i < N; i++) {
            if (a[i] != b[i]) ne[b[i]]++;
        }
        for (int i = 0; i < M; i++) ne[c[i]]--;
        bool se = false;
        for (int i = 0; i < N; i++) {
            if (ne[b[i]] > 0) se = true;
        }
        if (se) cout << "NO\n";
        else cout << "YES\n";
    }
}
