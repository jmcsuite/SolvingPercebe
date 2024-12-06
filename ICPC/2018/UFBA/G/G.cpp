#include <bits/stdc++.h>
#define float double
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

double X,A,T;
double degreesTime(double t, double one) {
    return (X/T)*360.0 + one*A/2;
}

const double PI = acos(-1);
double degree(ll x, ll y) {
    double c = sqrt(y*y + x*x);
    double d = acos(double(x)/double(c))*360.0/(2*PI);
    if (y >= 0) return d;
    return 360.0-d;
}

double timeDegree(double P) {
    return P*T/360.0;
}

const int maxn = 1e5;
ll vis[maxn];
double deg[maxn];
double ans[maxn];

ll cross(double d, double one) {
    ll dis = 1e12 + 1;
    ll ans = -1;
    while (dis) {
        if (degreesTime(X, one) >= 360.0 * double(ans+dis) + d) ans+=dis;
        else dis/=2;
    }
    return ans+1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N >> X;
    ll D;
    cin >> A >> T >> D;
    for (int i = 0; i < N; i++) {
        ll a,b; cin >> a >> b;
        if (a*a + b*b> D*D) vis[i] = 1;
        deg[i] = degree(a,b);
        if (deg[i] >= 360.0 - A/2.0) deg[i] -= 360.0;
    }

    for (int i = 0; i < N; i++) {
        if (vis[i]) continue;
        ll y = cross(deg[i], 1);
        ll x = cross(deg[i], -1);
        if (deg[i] >= -1.0*A/2.0 && deg[i] <= A/2.0) {
            if (x == 0) {
                ans[i] = X; 
                continue;
            }
            ans[i] = timeDegree(deg[i]+A/2.0);
            if (y == 1) continue;
            //y--; x--;
            ans[i] -= T*A/360.0;
        }
        if (y > x) ans[i] += timeDegree(degreesTime(X,1)-double(x)*360.0-deg[i]);
        ans[i] += double(x)*T*A/360.0;
    }
    cout << fixed << setprecision(7);
    for (int i = 0; i < N; i++) {
        if (vis[i]) cout << 0.0 << '\n';
        else cout << ans[i] << '\n';
    }
}
