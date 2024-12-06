#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
const int maxn = 1e3;
pll vl[maxn];

map<ll, ll> g;
map<ll, ll> c;

ll getGroup(ll i) {
    if (vl[i].first%2 && vl[i].second%2) return 3;
    if (vl[i].first%2) return 1;
    if (vl[i].second%2) return 2;
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    for (int i=0; i<N; i++) cin >> vl[i].first >> vl[i].second;
    for (int i=0; i<N; i++) {
        vl[i].first += 1e6;
        vl[i].second += 1e6;
    }
/*
    for (int i=0; i<N; i++) vl[i].first *= vl[i].first;
    for (int i=0; i<N; i++) vl[i].second *= vl[i].second;
*/
    while (1) {
        for (int i=0; i<N; i++) {
            int m = getGroup(i);
            g[i]=m;
            c[m]++;
        }

        bool se=true;
        for (int k=0; k<4; k++) if(c[k] == N) se=false;
        if (se) {
            if ((c[1] == 0 && c[2] == 0) || (c[0] == 0 && c[3] == 0)) {
                for (int k=0; k<4; k++) {
                    if (c[k] == 0) continue;
                    cout << c[k] << '\n';
                    for (int i=0; i<N; i++) {
                        if (g[i] != k) continue;
                        cout << i+1 << ' ';
                    }
                    cout << '\n';
                    return 0;
                }
            }

            cout << c[0] + c[3] << '\n';
            for (int i=0; i<N; i++) {
                if (g[i] != 0 && g[i] != 3) continue;
                cout << i+1 << ' ';
            }
            cout << '\n';
            return 0;
        }


        for (int k=0; k<4; k++) c[k]=0;
        for (int i=0; i<N; i++) vl[i].first /= 2;
        for (int i=0; i<N; i++) vl[i].second /= 2;
    }
}
