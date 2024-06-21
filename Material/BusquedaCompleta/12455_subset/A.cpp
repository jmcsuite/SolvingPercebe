#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 20;
ll vl[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll M, N; cin >> M >> N;
        for (int i = 0; i < N; i++) cin >> vl[i];
        bool ans = false;
        for (int i = 0; i < (1<<N); i++) {
            ll s = 0;
            for (int j = 0; j < N; j++)
                if(i & (1 << j)) s+= vl[j];
            if (s == M) ans = true;
        }
        cout << (ans ? "YES\n" : "NO\n");
    }
}
