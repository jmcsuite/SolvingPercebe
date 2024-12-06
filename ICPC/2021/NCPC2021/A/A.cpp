#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N, C;  cin >> N >> C;
    vll vl(N); 
    for (int i = 0; i < N; i++) cin >> vl[i];
    vll ans(N); 
    vll maxi(N);
    vll mini(N);
    maxi[0] = mini[0] = vl[0];
    for (int i = 1; i < N; i++) {
        maxi[i] = max(maxi[i-1], vl[i] + C*i);
        mini[i] = min(mini[i-1], vl[i] - C*i);
        ans[i] = max(ans[i], maxi[i]-vl[i]);
        ans[i] = max(ans[i], vl[i]-mini[i]);
        ans[i] = ans[i] - C *i;
    }
    for (int i = 0; i < N; i++) {
        cout << ans[i] << (i == N-1 ? '\n' : ' ');
    }
}
