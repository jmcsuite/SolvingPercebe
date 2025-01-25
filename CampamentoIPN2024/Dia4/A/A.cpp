#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

struct slope {
    ll m,a;
    double eval(double  x) { return x*m + a; }
};

struct cht {
    // gets minimum;
    // incleasing queries
    // non-increasing (decreasing) slopes
    list<slope> dq;

    bool remove(slope base, slope a, slope b) {
        ll deltaa = (base.a - a.a) * (b.m - base.m);
        ll deltab = (base.a - b.a) * (a.m - base.m);
        return deltaa >= deltab;
    }

    void add(slope x) {
        if (dq.empty()) {
            dq.push_back(x);
            return;
        }

        if (dq.size() == 1) {
            if (dq.back().m != x.m) {
                dq.push_back(x);
                return;
            }
            slope a = dq.back();
            dq.pop_back();
            if (a.a < x.a) dq.push_back(a);
            else dq.push_back(x);
            return;
        }

        slope a = dq.back();
        dq.pop_back();
        slope base = dq.back();
        while (remove(base, a , x)) {
            a = base;
            dq.pop_back();
            if (dq.empty()) break;
            base = dq.back();
        }
        dq.push_back(a);

        if (x.m != a.m) dq.push_back(x);
    }

    double getmin(double x) {
        if (dq.size() == 1) return dq.front().eval(x);
        slope a = dq.front();
        dq.pop_front();
        slope b = dq.front();
        while (b.eval(x) <= a.eval(x)) {
            a = b;
            dq.pop_front();
            if (dq.empty()) break;
            b = dq.front();
        }
        dq.push_front(a);
        return dq.front().eval(x);
    }
};

struct segment {
    ll xl, xr, y;
    bool operator < (const segment& other) const {
        return y < other.y;
    }
};


struct frac {
    ll x,y;
    bool operator < (const frac& other) const {
        return x*other.y < other.x * y;
    }
};

struct point {
    ll x, y, in;
    bool operator < (const point& other) const {
        return y < other.y;
    }
};

const int maxn = 2e3;
point points[2*maxn];
frac in[maxn+1];
frac out[maxn+1];
segment segments[maxn];
pair<frac,ll> temp[maxn][2*maxn + 2];
ll rows[maxn];
pair<frac,ll> ans[2*maxn + 2];
pair<frac,ll> aa[(2*maxn+2)*maxn];

const int INF = 1e9 + 7;
ll n;

// get slope
frac get_slope(point origin, point x2) {
    return {x2.x - origin.x, origin.y - x2.y};
}


ll merge_segments() {
    ll totalsize = 0;
    for (int i=0; i<n; i++) totalsize += rows[i];
    ll idx = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<rows[i]; j++,idx++) aa[idx] = temp[i][j];
    }

    for (int i=0; i<totalsize; i++) aa[i].second *= -1;

    sort(aa, aa+totalsize);

    ll nnodes = 0;
    ll sum = 0;
    frac prev = {-1*INF, 1};
    for (int i =0; i<totalsize; i++) {
        if (sum == n * -1) {
            ans[nnodes++] = {prev,1};
            ans[nnodes++] = {aa[i].first, -1};
        }
        sum += aa[i].second;
        prev = aa[i].first;
    }
    return nnodes;
}

void merge_points(int npoints, int row) {
    sort(in, in+npoints);
    sort(out, out+npoints);

    ll seg = 0;
    for (int i=0; i<npoints; i++) {
        if (out[i] < in[i]) continue;
        temp[row][seg++] = {in[i],1};
        temp[row][seg++] = {out[i],-1};
    }
    rows[row] = seg;
}

cht cmin,cmax;

double calc(frac f) {
    double minx = cmin.getmin(double(f.x)/double(f.y));
    double maxx = cmax.getmin(double(f.x)/double(f.y)) * -1;
    return maxx - minx;
}

double calculate(ll sizn) {
    if (sizn <= 2) return calc({0,1});
    double cc = calc(ans[1].first);
    for (ll i=1; i + 1 < sizn; i++) cc = min(cc, calc(ans[i].first));
    return cc;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for (int i=0; i<n; i++) cin>>segments[i].xl>>segments[i].xr>>segments[i].y;

    for (int i=0; i<n; i++) {
        points[i*2].x = segments[i].xl;
        points[i*2].y = segments[i].y;
        points[i*2].in = 1;

        points[i*2+1].x = segments[i].xr;
        points[i*2+1].y = segments[i].y;
        points[i*2+1].in = -1;
    }

    for (int i=0; i<n; i++) {
        ll npoints=0;
        in[npoints] = {-1*INF,1};
        out[npoints] = {INF,1};
        npoints++;
        for (int j=0; j<2*n; j+=2) {
            if (points[j].y >= segments[i].y) continue;
            in[npoints] = get_slope(points[i*2], points[j+1]);
            out[npoints] = get_slope(points[i*2+1], points[j]);
            npoints++;
        }
        merge_points(npoints, i);
    }


    ll sizn = merge_segments();

    sort(points, points + 2*n);
    for (int i = 2*n-1; i>=0; i--) cmin.add({points[i].y, points[i].x});
    for (int i=0; i<2*n; i++) cmax.add({points[i].y * -1, points[i].x * -1});

    double calc = calculate(sizn);
    cout << fixed << setprecision(7);
    cout << calc << '\n';
}
