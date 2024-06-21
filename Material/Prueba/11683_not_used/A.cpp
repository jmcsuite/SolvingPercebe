#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e4;
ll vl[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll M, N;
    while(cin>>M>>N, M && N) {
        for (int i = 0; i < N; i++) cin >> vl[i];

        ll ans = 0;
        ll prev = M;
        for (int i = 0; i < N; i++) {
            ans += max(0LL, prev-vl[i]);
            prev = vl[i];
        }
        cout << ans << '\n';
    }
}
