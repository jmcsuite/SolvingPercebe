#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int mod = 1e9 + 7;

ll M; 

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> M;
    ll ans = 0;
    for (int N = 1; N <= M; N++) {
        // ll prev = ans;
        ll x = M-2*N;
        if (x <= 0) break;
        if (x >= N) {
            ll j = N/2;
            if (N%2) j++;
            ans = (ans + N*j - j*(j-1)) % mod;
        }
        else {
            ll i = (N-x)/2; i++;
            ans = (ans + x*i) % mod;
            ll dis_j = (N-2*i);
            ll j = dis_j / 2;
            if (dis_j%2) j++;
            if (dis_j >= 0) {
                ans = (ans + dis_j*j - j*(j-1)) % mod;
            }
        }
        // cout << N << ' ' << ans-prev << endl;
    }

    ans = (ans%mod + mod)%mod;
    cout << ans << '\n';
}
