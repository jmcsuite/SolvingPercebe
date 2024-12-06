#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6;
double x[maxn], y[maxn], vx[maxn], vy[maxn];

const double maxarea = 4e18;
ll N;
double area(double t) {
    double maxx = x[0] + vx[0]*t;
    double minx = x[0] + vx[0]*t;
    double maxy = y[0] + vy[0]*t;
    double miny = y[0] + vy[0]*t;

    for (int i=0; i<N; i++) {
        maxx = max(maxx, x[i]+vx[i]*t);
        minx = min(minx, x[i]+vx[i]*t);
        maxy = max(maxy, y[i]+vy[i]*t);
        miny = min(miny, y[i]+vy[i]*t);
    }

    double d1 = maxx-minx;
    double d2 = maxy-miny;
    if (maxarea/d1 <= d2) return maxarea;
    return d1*d2;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i=0; i<N; i++) {
        ll a,b,c,d; cin >> a >> b >> c >> d;
        x[i] = a; 
        y[i] = b;
        vx[i] = c;
        vy[i] = d;
    }

    double l = 0;
    double r = 1e9;
    double eps = 1e-16;

    ll it = 0;
    while (r-l > eps && it <= 1000) {
        double a1 = area((r-l)/3 + l);
        double a2 = area(2*(r-l)/3 + l);
        if (a2 >= a1) r = 2*(r-l)/3 + l;
        else l = (r-l)/3+l;
        it++;
    }
    cout << fixed << setprecision(11);
    cout << area(l) << '\n';
}
