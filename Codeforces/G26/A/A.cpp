#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        vector<ll> vl(N); for(int i = 0; i < N; i++) cin >> vl[i];
        if (vl[0] == vl[N-1]) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        for (int i = 0; i  < N-2; i++) cout << "R";
        cout << "BR\n";
    }
}
