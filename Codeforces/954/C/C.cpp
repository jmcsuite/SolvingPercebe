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
        ll N, M; cin >> N >> M;
        string a; cin >> a;
        for (int i = 0; i < M; i++) cin >> vl[i];
        for (int i = 0; i < M; i++) vl[i]--;
        string b; cin >> b;

        sort(vl, vl + M);
        sort(b.begin(), b.end());
        //cout << b << '\n';
        ll j = 0;
        //cout << a << '\n';
        for (int i = 0; i < M; i++) {
            if (i > 0 && vl[i] == vl[i-1]) continue;
            a[vl[i]] = b[j];
            j++;
        }
        cout << a << '\n';
    }
}
