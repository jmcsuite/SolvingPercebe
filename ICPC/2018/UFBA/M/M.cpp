#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    ll x = 10; 

    vector<ll> ans;
    ll z = N;
    //ll cc = 0;
    while (z >= 32) {
        z = (N+x-1)/x;
        ans.push_back(x);
        //cc += (x)*(4);
        x = x*10;
    }

    cout << ans.size() + 1 << '\n';
    for (ll a : ans) {
        z = (N+a-1)/a;
        cout << z << '\n';
        for (int k = 0; k < z; k++) {
            cout << k*a+1 << ' ' << min((k+1)*a,N) << '\n';
        }
    }

    cout << 1 << '\n';
    cout << 1 << ' ' << N << '\n';
    /*cc += N * 5; 

    cout << "cost: " << cc << '\n';
    if (cc > N*7) { return -1; };
    */
}
