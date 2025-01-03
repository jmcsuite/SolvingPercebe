#include <bits/stdc++.h>
using namespace std;
using ll = int;
using pll = pair<ll,ll>;
using vll = vector<ll>;
const int maxn = 2000;

pll vl[maxn];
ll dp[maxn][maxn];

ll ff(ll x) {
    for (int i=0; i<maxn; i++) if (vl[i].first == x) return vl[i].second;
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    for (int i=0; i<N; i++) {
        cin>>vl[i].first;
        vl[i].second = i+1;
    }

    sort(vl, vl+N);

    ll ans = 1;
    pll ansinit(vl[0].first, 0);
    for (int i=N-1; i>=0; i--) {
        for (int j=i+1, k=i+1; j<N; j++) {
            ll delta = vl[j].first - vl[i].first;
            while (k < N && (vl[j].first + delta > vl[k].first)) k++;
            if (k >= N || (vl[j].first + delta != vl[k].first)) dp[i][j] = 2;
            else dp[i][j] = 1 + dp[j][k];
            if (dp[i][j] > ans) {
                ans = dp[i][j];
                ansinit = {vl[i].first, delta};
            }
        }
    }

    cout << ans << '\n';
    for (int i=0,j=ansinit.first; i<ans; i++,j+=ansinit.second) {
        cout << ff(j) << (i+1 == ans ? '\n' : ' ');
    }
}
