#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    while (N--) {
        string a, b;
        cin >> a >> b;
        char c = b[0];
        b[0] = a[0];
        a[0] = c;
        cout << a << ' ' << b << '\n';
    }
}
