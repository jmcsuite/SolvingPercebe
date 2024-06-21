#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<double,double>;
using vpll = vector<pll>;
const double EPS = 0;

int solve(vpll& vl, double w) {
    double maxi = 0;
    int ans = 0;
    for (int i = 0; i < (int)vl.size(); i++) {
        //cout << " maxi " << maxi << ' ' << i << endl;
        if (maxi + EPS >= w) break;
        if (vl[i].first > maxi + EPS) break;
        int j = i;
        while (j < (int)vl.size() && vl[j].first <= maxi + EPS) j++;
        for (int k = i; k < j; k++) {
            maxi = max(maxi, vl[k].second);
        }
        ans++;
        i = j-1;
    }
    if (maxi + EPS >= w) return ans;
    return -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, L, W;
    while (cin >> N >> L >> W) {
        double w = W; w/= 2;
        double l = L;
        vpll vp; 
        for (int i = 0; i < N; i++) {
            ll a,b; cin >> a >> b;
            if ( b * 2 <= W) continue;
            double dis = double(b) * double(b) - (w*w);
            dis = sqrt(dis);
            double iz = double(a) - dis;
            double der = double(a) + dis;
            //cout << i << ' ' << iz << ' ' << der << '\n';
            vp.push_back({iz,der});
        }
        //for (int i = 0; i < N; i++) cout << vp[i].first << ' ' << vp[i].second  << endl;
        sort(vp.begin(), vp.end());
        cout << solve(vp, l) << '\n';
    }
}
