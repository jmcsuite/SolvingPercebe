#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n = 50000;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << n << '\n';
    for (int i=2; i<=n; i++) cout << i-1 << ' ' << i << '\n';
}
