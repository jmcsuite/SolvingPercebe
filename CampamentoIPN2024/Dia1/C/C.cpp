#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<ll>;

const int maxn = 1e3;
int vadj[maxn][maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> vadj[i][j];

    vector<pll> r;
    vector<pll> c;

    for (int i = 0; i < N; i++) {
        ll s = 0;
        for (int j = 0; j < N; j++) s += vadj[i][j];
        r.push_back({s,i});
    }

    for (int i = 0; i < N; i++) {
        ll s = 0;
        for (int j = 0; j < N; j++) s += vadj[j][i];
        c.push_back({s, i});
    }

    sort(r.begin(), r.end()); 
    sort(c.begin(), c.end());


    if(r[0].first != r[1].first && c[0].first != c[1].first) {
        cout << ++r[0].second << ' ' << ++c[0].second << '\n';
        cout << ++r[N-1].second << ' ' << ++c[N-1].second << '\n';
        return 0;
    }

    if (r[0].first != r[1].first) {
        ll dx = r[1].first - r[0].first;

        ll r1 = r[0].second;
        ll r2 = r[N-1].second;
        for (int i = 0; i < N; i++) {
            if (vadj[r2][i] - vadj[r1][i] == dx) {
                cout << ++r1 << ' ' << ++i << '\n';
                cout << ++r2 << ' ' << i << '\n';
                return 0;
            }
        }
    }

    ll dx = c[1].first - c[0].first;
    ll c1 = c[0].second;
    ll c2 = c[N-1].second;
    for (int i = 0; i < N; i++) {
        if (vadj[i][c2] - vadj[i][c1] == dx) {
            cout << ++i << ' ' << ++c1 << '\n';
            cout << i << ' ' << ++c2 << '\n';
        }
    }
    
}
