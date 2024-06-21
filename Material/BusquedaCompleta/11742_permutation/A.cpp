#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<ll>;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N,M; 
    while (cin >> N >> M, N || M) {
        vll vl(N); 
        for (int i = 0; i < N; i++) vl[i] = i;
        vector<pair<pll,ll>> vp(M);
        for (int i = 0; i < M; i++) cin >> vp[i].first.first >> vp[i].first.second >> vp[i].second;

        ll ans = 0;
        do {
            bool se = true;
            vll pos(N);
            for(int i = 0; i < N; i++) pos[vl[i]] = i;

            for (int i = 0; i < M; i++) {
                ll dx = pos[vp[i].first.first] - pos[vp[i].first.second];
                dx = max(dx, dx*-1);

                if (vp[i].second < 0 && dx < vp[i].second*-1) se = false;
                else if (vp[i].second > 0 && dx > vp[i].second) se = false;
            }
            if (se) ans++;
        }while (next_permutation(vl.begin(), vl.end()));

        cout << ans << '\n';
    }
}
