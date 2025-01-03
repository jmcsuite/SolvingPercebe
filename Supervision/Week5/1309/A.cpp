#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int mod = 9973;

ll g(ll x, ll y) {
    x%=mod;
    ll x5 = ((((x*x)%mod) * ((x*x) % mod))%mod) * x;
    x5 %= mod;
    ll x3 = (x*x)%mod *  x;

    ll ans = ((y-1) * x5) % mod + x3 - x*y + 3*x + 7*y;
    ans %= mod;
    return ans;

}

const int block = 1e5;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; N = 1e8; 
    vll vl(N+1); vl[0] = 0;
    for (int i=1; i<=N; i++) {
        vl[i] = g(i,vl[i-1]);
    }

    cout << "ll vl[";
    cout << (N)/block + 1; 
    cout << "] = {0";
    for (int i=block; i<=N; i+=block) {
        cout << "," << vl[i];
    }
    cout << "};";
}
