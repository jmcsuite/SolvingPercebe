#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 13;
ll vl[maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    bool first = true;
    ll N;
    while(cin >> N, N) {
        if(!first) cout << '\n';
        first = false;
        for(int i = 0; i < N; i++) cin >> vl[i];

        for (int a = 0; a < N; a++) {
            for (int b = a+1; b < N; b++) {
                for (int c = b+1; c < N; c++) {
                    for (int d = c+1; d < N; d++) {
                        for (int e = d+1; e < N; e++) {
                            for (int f = e+1; f < N; f++) {
                                cout << vl[a] << ' ' << vl[b] << ' ' << vl[c] << ' ' << vl[d] << ' ' << vl[e] << ' ' << vl[f] << '\n';
                            }
                        }
                    }
                }
            }
        }
    }
}
