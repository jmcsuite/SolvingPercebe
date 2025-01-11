#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 32;
ll disk[maxn];
ll vl[maxn];
ll n;
ll calc() {
    ll ans = 0;
    for (int i=n; i>=1; i--) {
        if (vl[i] == disk[i]) continue;
        ll a = 1;
        if (a == vl[i] || disk[i] == a) a++;
        if (a == vl[i] || disk[i] == a) a++;

        for (int j=1; j<i; j++) vl[j] = a;
        vl[i] = disk[i];
        ans += (1ll << (i-1));
    }
    return ans;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for (int i=1; i<=n; i++) vl[i] = 1;
    for (int i=1; i<=n; i++) cin>>disk[i];

    ll ans = calc();

    ll notans = 0;
    for (int i=1; i<=n; i++) vl[i] = 2;
    notans = calc();
    ll tot = (1ll << n) - 1;

    if (ans + notans != tot) {
        cout << -1 << '\n';
        return 0;
    }
    cout << ans << '\n';
}

