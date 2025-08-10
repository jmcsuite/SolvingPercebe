#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

double intersect();
double Y,X;

double calc(double x, double y) {
    double dis = y*y + x*x;
    double deltax = (X-x); 
    double deltay = (Y-y);
    deltax *= deltax;
    deltay *= deltay;

    return sqrt(dis) + sqrt(deltax) + sqrt(deltay);
}

double intersert(double x, double y, double x2, double y2) {
    double res = (y2 - y)*(x)*x2;
    res /= ((y2*x - y*x2));
    return res;
}

int main() {
    ll n,t; cin>>n>>t;
    ll x,y; cin>>x>>y;
    X = x;
    Y = y;
    vector<pair<ll,pll>> vp;
    vp.push_back({t+10, {x,y}});

    for (int i=0; i<n; i++) {
        ll s; cin>>s>>x>>y;
        vp.push_back({s,{x,y}});
    }
    

    for (int i=0; i<t; i++) {
        double ax, ay, ans;
        ans = 1e18;
        for (int a = 0; a<=n; a++) {
            for (int b = 0; b<=n; b++) {
                ax = vp[a].second.first;
                ay = vp[b].second.second;
                bool se = true;
                for (int j=0; j<=n; j++) {
                    if (j == a) continue;
                    if (j == b) continue;
                    if (vp[j].first > i) continue;
                    double iii = intersert(ax, ay, vp[j].second.first, vp[j].second.second);
                    if (iii <= 0 || iii >= ax) continue;
                    se = false;
                }
                if (se) ans = min(ans, calc(ax, ay));
            }
        }
        ll pp = ans;
        cout << pp << '\n';
    }
}

