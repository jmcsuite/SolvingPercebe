#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5;

ll vl[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        for (int i = 0; i < N; i++) cin >> vl[i];
        for (int i = N-2; i >= 0; i--) vl[i] = max(vl[i], vl[i+1] + 1);
        cout << vl[0] << '\n';
    }
}
