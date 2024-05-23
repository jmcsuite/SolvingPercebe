#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll a,b,c;
    cin >> a >> b >> c;
    for (int i = 1; i <= c; i++) {
        cout << a*i + b << (i == c ? '\n' : ' ');
    }
}
