#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5;
const int maxk = 20;

int vl[maxn];
ll T, N;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>T;
    while (T--) {
        cin >> N;
        for (int i = 0; i < N; i++) cin >> vl[i];
        ll ans = 1;
        ll j,k;
        for (k = 0, j = (1<<k); k < maxk; k++, j = (1<<k)) {
            ll dis = 0;
            for (int i = 0; i < N; i++) {
                dis++;
                if ((vl[i] & j)) {
                    ans = max(ans, dis);
                    dis = 0;
                }
            }
            dis++;
            if (dis == N+1) dis = 1;
            ans = max(ans, dis);
        }
        cout << ans << '\n';
    }
}
