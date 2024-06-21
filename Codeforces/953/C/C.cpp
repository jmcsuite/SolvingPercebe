#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N, k; cin >> N >> k;
        if (k%2) {
            cout << "No\n";
            continue;
        }
        k/=2;
        ll sum_max = 0; 
        for (int i = 0; i < N/2; i++) sum_max += (N-2*i-1);
        if (sum_max < k) {
            cout << "No\n";
            continue;
        }
        cout << "Yes\n";

        vll vl(N);
        for (int i = 0; i < N; i++) vl[i] = i+1;
        for (int i = 0; i < N/2; i++) {
            if (k > (N-2*i - 1)){
                swap(vl[i], vl[N-i-1]); //this adds N - 2*i - 1
                k-= N-2*i-1;
            }
            else {
                swap(vl[i], vl[i+k]); //this adds k
                k -= k;
            }
        }
        
        for (int i = 0; i < N; i++) cout << vl[i] << (i == N-1 ? '\n' : ' ');
    }
}
