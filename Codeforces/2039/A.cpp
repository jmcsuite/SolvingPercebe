#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        cout << 1 << ' ';
        for (int i=2; i<=N; i++) cout << i+i-1 << ' ';
        cout << '\n';
    }
}
