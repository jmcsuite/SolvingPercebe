#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    vll vl(N);
    for (int i = 0; i < N; i++) cin >> vl[i];
    map<ll,ll> mp;
    for (int i = 0; i < N; i++) mp[vl[i]-i]++;

    ll ans = 0;
    ll x = mp.begin()->first;
    for (int i = 0; i < N; i++) ans = (ans + abs(x + i - vl[i]));

    ll m = 0;
    ll z = ans;
    for (pll p : mp) {
        ll dx = p.first - x;
        x = p.first;
        ans = (ans + m*dx - (N-m)*dx);
        z = min(ans, z);

        m += p.second;
    }
    cout << z << '\n';
}
