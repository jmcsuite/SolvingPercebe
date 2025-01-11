#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 50;
ll row[maxn];
ll col[maxn];
ll dd[2*maxn];
ll ee[2*maxn];
ll n;

ll delta[2][3] = {{1,2,0}, {2,0,1}};
pll p[maxn];
void rem(ll i) {
    pll a = p[i];
    dd[a.first + a.second]--;
    ee[a.first - a.second + n - 1]--;
}

void add(ll i) {
    pll a = p[i];
    row[i] = a.first;
    col[i] = a.second;
    dd[a.first + a.second]++;
    ee[a.first - a.second + n - 1]++;
}

ll sol(ll i, ll j, ll k) {
    vll cc;
    cc.push_back(col[i]);
    cc.push_back(col[j]);
    cc.push_back(col[k]);

    ll ans = 0;
    for (int z=0; z<2; z++) {
        ll ri = row[i];
        ll rj = row[j];
        ll rk = row[k];

        ll ci = cc[delta[z][0]];
        ll cj = cc[delta[z][1]];
        ll ck = cc[delta[z][2]];

        if (dd[ri+ci] || ee[ri-ci+n-1]) continue;
        if (dd[rj+cj] || ee[rj-cj+n-1]) continue;
        if (dd[rk+ck] || ee[rk-ck+n-1]) continue;

        if ((ri+ci) == (rj+cj)) continue;
        if ((rk+ck) == (rj+cj)) continue;
        if ((rk+ck) == (ri+ci)) continue;

        if ((ri-ci) == (rj-cj)) continue;
        if ((rk-ck) == (rj-cj)) continue;
        if ((ri-ci) == (rk-ck)) continue;
        ans++;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for (int i=0; i<n; i++) {
        cin>>p[i].first>>p[i].second;
        --p[i].first;
        --p[i].second;
        add(i);
    }

    ll ans = 0;
    for (int i=0; i<n; i++) {
        rem(i);
        for (int j=i+1; j<n; j++) {
            rem(j);
            for (int k=j+1; k<n; k++) {
                rem(k);
                ans += sol(i,j,k);
                add(k);
            }
            add(j);
        }
        add(i);
    }

    cout << ans << '\n';
}
