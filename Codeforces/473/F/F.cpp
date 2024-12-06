#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 1e9 + 7;
const int maxn = 1e5;

ll pp[maxn+1];

void pre() {
    pp[0] = 1;
    for (int i = 1; i <= maxn; i++) pp[i] = (2 * pp[i-1]) % mod;
}

ll basis[20];
ll vl[maxn];
ll sum[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    pre();

    ll N, Q; cin >> N >> Q;
    for (int i = 0; i < N; i++) cin >> vl[i];
    ll D = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < D; j++) {
            if ((vl[basis[j]] ^ vl[i]) < vl[i]) vl[i] = vl[i] ^ vl[basis[j]];
        }
        if (vl[i] == 0) sum[i] = 1;
        else basis[D++] = i;
    }

    for (int i = 1; i < N; i++) sum[i] += sum[i-1];

    while (Q--) {
        ll l, x; cin >> l >> x;
        for (int j = 0; j < D; j++) {
            if (basis[j] >= l) break;
            if ((vl[basis[j]] ^ x) < x) x = x ^ vl[basis[j]];
        }
        if (x != 0) {
            cout << 0 << '\n';
            continue;
        }
        cout << pp[sum[--l]] << '\n';
    }
}
