#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn = 100000;
pll vl[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    bool se = false;
    ll T; cin >> T;
    while (T--) {
        if (se) cout << '\n';
        se = true;
        ll M; cin >> M;
        ll N = 0;
        ll a, b;
        while (cin >> a >> b , a || b) {
            vl[N].first = a;
            vl[N].second = b;
            N++;
        }
        ll ans = 0;
        sort(vl, vl + N);
        

        vpll vp;
        for (int i = 0; i < N; i++) {
            if (ans >= M) break;
            if (vl[i].first > ans) break;

            ll j = i;
            while (j < N && vl[j].first <= ans) j++;
            pll pl;
            for (int k = i; k < j; k++) {
                if (vl[k].second > ans) {
                    pl = vl[k];
                    ans = vl[k].second;
                }
            }
            vp.push_back(pl);
            i = j-1;
        }
        if (ans < M) cout << "0\n";
        else {
            cout << vp.size() << '\n';
            for (auto p : vp) cout << p.first << ' ' << p.second << '\n';
        }
    }
}
