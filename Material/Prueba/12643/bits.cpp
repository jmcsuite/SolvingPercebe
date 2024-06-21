#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,a,b;
    while(cin >> N >> a >> b) {
        a--; b--;
        for (int i = N-1; i >= 0; i--) {
            if ((a & (1<<i)) != ((b & (1<<i)))) {
                cout << i+1 << '\n';
                break;
            }
        }
    }
}
