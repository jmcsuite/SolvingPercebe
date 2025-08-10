#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
const int maxn = 2e5 + 10;
pll vl[maxn];
vector<pll> ans;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n; cin>>n;
    for (int i=1; i<=n; i++) cin>>vl[i].first>>vl[i].second;

    for (int i=n; i>0; i--) {
        ll deltae = vl[i].second - vl[i-1].second;
        ll mink = (deltae / 3) + ((deltae%3) ? 1 : 0);
        if (vl[i-1].second + mink > vl[i].first) {
            vl[i-1].second = vl[i].second;
        }
        else {
            ans.push_back({vl[i-1].second, mink});
        }
    }

    if (vl[0].second != 0) {
        cout << "impossible\n";
        return 0;
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (pll p: ans) cout << p.first << ' ' << p.first + p.second << '\n';
}

    
