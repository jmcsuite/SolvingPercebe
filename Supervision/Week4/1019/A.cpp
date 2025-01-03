#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<pll>;

vll ans;

void black(pll p) {
    vll a;
    for (pll x: ans) {
        if (x.first >= p.first && x.second <= p.second) continue;
        if (x.second <= p.first) {
            a.push_back(x);
            continue;
        }
        else if (x.first >= p.second) {
            a.push_back(x);
            continue;
        }

        if (p.first > x.first) a.push_back({x.first, p.first});
        if (p.second < x.second) a.push_back({p.second, x.second});
    }
    swap(ans,a);
    sort(ans.begin(), ans.end());
}

void white(pll p) {
    vll a;
    for (pll x: ans) {
        if (x.first > p.second) {
           a.push_back(x);
           continue;
        } 
        if (x.second < p.first) {
            a.push_back(x);
            continue;
        }
        if (p.first >= x.first && p.second <= x.second) return;
        if (x.first >= p.first && x.second <= p.second) continue;
        p.second = max(p.second, x.second);
        p.first = min(p.first, x.first);
        continue;
    }
    a.push_back(p);
    swap(ans,a);
    sort(ans.begin(), ans.end());
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ans.push_back({0,1e9});

    ll M; cin>>M;
    while (M--) {
        pll p; char c; cin>>p.first>>p.second>>c;
        if (c == 'b') black(p);
        else white(p);
    }

    sort(ans.rbegin(), ans.rend(), [&](pll a, pll b) {
            ll sa = a.second - a.first;
            ll sb = b.second - b.first;
            if (sa != sb) return sa<sb;
            return a.first > b.first;
            });
    cout << ans[0].first << ' ' << ans[0].second << '\n';
}
