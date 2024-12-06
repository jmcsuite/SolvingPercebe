#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 4e5 + 1;

ll vl[maxn];
ll a[maxn];
ll b[maxn];

ll q[maxn];

void solve() {
    ll N, M; cin >> N >> M;
    for (int i = 0; i <= N+M; i++) cin >> a[i];
    for (int i = 0; i <= N+M; i++) cin >> b[i];

    ll ca, cb; ca = cb = 0;

    for (int i = 0; i <= N+M; i++) {
        if (ca == N) vl[i] = b[i];
        else if (cb == M) vl[i] = a[i];
        else if (a[i] > b[i]) {
            ca++; 
            vl[i] = a[i];
        }
        else {
            cb++;
            vl[i] = b[i];
        }
    }

    vl[N+M] = 0;
    ll la = N+M; 
    ll lb = N+M;

    ll sum = 0;
    for (int i = 0; i <= N+M; i++) sum += vl[i];
    q[N+M] = sum;

    for (int i = N+M-1; i >= 0; i--) {
        ll ai = sum - vl[i];

        if (vl[i] == a[i]) {
            ai += b[N+M]; ai -= b[la]; ai += a[la];
        }
        else {
            ai += a[N+M]; ai -= a[lb]; ai += b[lb];
        }

        if (a[i] > b[i] && vl[i] == b[i]) la = i;
        else if (b[i] > a[i] && vl[i] == a[i]) lb = i;

        q[i] = ai;
    }

    for (int i = 0; i <= N+M; i++) cout << q[i] << ' ';
    cout << '\n';
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) solve();
}
