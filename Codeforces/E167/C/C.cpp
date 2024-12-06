#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5;
ll a[maxn], b[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        for (int i = 0; i < N; i++) cin >> a[i];
        for (int i = 0; i < N; i++) cin >> b[i];
        ll sum_a, sum_b, pos, neg; sum_a = sum_b = pos = neg = 0;
        for (int i = 0; i < N; i++) {
            if (a[i] == b[i] && b[i] == -1) neg++;
            if (a[i] == b[i] && a[i] == 1) pos++;
            if (a[i] == b[i]) continue;
            ll maxi = max(a[i], b[i]);
            if (a[i] == maxi) sum_a += maxi;
            else sum_b += maxi;
        }


        //cout << sum_a << ' ' << sum_b << ' ' << pos << ' ' << neg << '\n';
        if (sum_b > sum_a) swap(sum_b, sum_a);

        ll delta = sum_a - sum_b;
        sum_b += min(delta, pos); 
        pos -= min(delta, pos);
        sum_b += pos/2;
        sum_a += pos/2 + pos%2;

        ll d2 = sum_a - sum_b;
        sum_a -= min(d2, neg);
        neg -= min(d2, neg);
        sum_a -= neg/2;
        sum_b -= neg/2 + neg%2;

        cout << sum_b << '\n';
    }
}
