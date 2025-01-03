#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);


    ll N,K,M;
    cin >> N >> K >> M;
    for (int i=0, j=0; i<N; i++,j=(j+1)%K) {
        cout << j+1 << '\n';
    }

    for (int i=0; i<N-1; i+=2) {
        cout << i+1 << ' ' << i+2 << '\n';
        M--;
    }

    if (N%2) {
        cout << N-1 << ' ' << N << '\n';
        M--;
    }

    for (int i=0; i<N; i++) {
        if (M == 0) break;
        for (int j=i+1; j<N; j++) {
            if (M == 0) break;
            if (i%2 == 0 && j == i+1) continue;
            if (i == N-2 && j == N-1 && (N%2) == 1) continue;
            if (i%K == j%K) continue;
            
            M--;
            cout << i+1 << ' ' << j+1 << '\n';
        }
    }
}
