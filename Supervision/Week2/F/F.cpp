#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

ll bin_exp(ll a) {
    return a*a*a;
}

ll finda(ll x) {
    ll ans = 0; ll dis = 1e5;
    while (dis) {
        if (ans + dis <= 1e5 && bin_exp(ans+dis) <= x) ans+=dis;
        else dis/=2;
    }
    return ans;
}


pll solve(ll res) {
    if (res == 0) return {0,0};
    ll a1 = finda(res);
    pll x1 = solve(res - bin_exp(a1));
    ++x1.first; x1.second+=bin_exp(a1);

    if (a1 == 1) return x1;
    ll a2 = a1-1;
    pll x2 = solve(bin_exp(a1) - 1 - bin_exp(a2));
    ++x2.first; x2.second+=bin_exp(a2);
    return max(x1, x2);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll M; cin>>M;
    pll ans = solve(M);
    cout << ans.first << ' ' << ans.second << '\n';
}
