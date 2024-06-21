#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 20;

ll N, K, M;
ll res[maxn][maxn];
ll res_c[maxn];
ll res_cc[maxn];

ll per[maxn];
ll vl[maxn];

ll T;
ll save[maxn];

ll calc() {
    ll ans = 0;
    for (int i = 0; i < N; i++) if (per[i]) ans += vl[i];

    for (int i = 0; i < M; i++) {
        ll cc = 0;
        for (int j = 0; j < res_cc[i]; j++) {
            if (per[res[i][j]]) cc++;
        }
        if (cc == 0) continue;
        ans = (ans - (cc-1)*res_c[i]);
    }
    return ans;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while (cin >> N >> K, N || K) {
        for (int i = 0; i < N; i++) cin >> vl[i];
        cin >> M;
        for (int i = 0; i < M; i++) {
            cin >> res_cc[i];
            for (int j = 0; j < res_cc[i]; j++) {
                cin >> res[i][j];
                res[i][j]--;
            }
            cin >> res_c[i];
        }

        for (int i = 0; i < N-K; i++) per[i] = 0;
        for (int i = N-K; i < N; i++) per[i] = 1;
        ll maxi = 0;
        do {
            ll x = calc();
            maxi = max(maxi, x);
            if (x == maxi) {
                for (int i = 0; i < N; i++) save[i] = per[i];
            }
        } while (next_permutation(per, per+N));

        cout << "Case Number  " << ++T << '\n';
        cout << "Number of Customers: " << maxi << '\n';
        cout << "Locations recommended:";
        for (int i = 0; i < N; i++) {
            if (save[i]) cout << " " << i+1;
        }
        cout << '\n';
        cout << '\n';
    }
}
