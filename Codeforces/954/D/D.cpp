#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 21;

ll N; 
ll vl[maxn];



int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        cin >> N;
        string a; cin >> a;
        for (int i = 0; i < N; i++) vl[i] = a[i] - '0';

        ll ans = 1e17;
        for (int i = 0; i < N-1; i++) {
            vector<ll> v;
            for (int j = 0; j < N; j++) {
                if (j == i) {
                    v.push_back(10*vl[j] + vl[j+1]);
                    j++;
                }
                else {
                    v.push_back(vl[j]);
                }
            }
            bool c = false;
            for (int j = 0; j < N-1; j++) if(v[j] == 0) c = true;
            if (c) ans = 0;
            ll cur = 0;
            for (int j = 0; j < N-1; j++) {
                if (v[j] == 1) continue;
                cur += v[j];
            }
            if (cur == 0) cur++;
            ans = min(ans, cur);
        }
        cout << ans << '\n';
    }
}
