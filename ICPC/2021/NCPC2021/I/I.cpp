#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
const int mod = 1e9 + 7;
const int maxn = 1e6 + 1;

ll arr[maxn];
ll arr2[maxn];
ll pp[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    srand(time(NULL));
    pp[0] = 1;
    for (int i = 1; i < maxn; i++) pp[i] = (2*pp[i-1])%mod;

    map<ll,ll> mp;
    map<ll,ll> m2;
    for (int i = 0; i < N; i++) {
        ll x; cin >> x; 
        if (mp.find(x) == mp.end()) mp[x] = rand()*rand();
        if (m2.find(x) == m2.end()) m2[x] = rand()*rand();
        arr[i] += mp[x];
        arr2[i] += m2[x];
    }
    for (int i = 0; i < N; i++) {
        ll x; cin >> x; 
        arr[i] -= mp[x];
        arr2[i] -= m2[x];
        if (i > 0) arr[i] += arr[i-1];
        if (i > 0) arr2[i] += arr2[i-1];
    }
    map<pll,ll> cc;
    for (int i = 0; i < N; i++) cc[{arr[i],arr2[i]}]++;
    ll ans = 0;
    for (auto x : cc) {
        ans = (ans + pp[x.second] - x.second - 1) % mod;
    }
    ans = (ans + mod)%mod;
    cout << ans << '\n';
}
