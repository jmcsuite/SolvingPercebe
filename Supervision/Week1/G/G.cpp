#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
    ll x,y; 
    Point() : x(0), y(0) {}
    Point(ll a, ll b) : x(a), y(b) {}
};

ll maxx, maxy, minx, miny;
void setup() {
    maxx = 1e18;
    maxy = 1e18;
    minx = -1e18;
    miny = -1e18;
}

ll iterate(Point b, Point c, ll it) {
    if (it == 0) {
        if (c.y > b.y) return 3;//(it-1)
        return it+1;
    }

    if (it == 1) {
        if (c.x < b.x) return it+1; 
        return it-1;
    }

    if (it == 2) {
        if (c.y > b.y) return it+1;
        return it-1;
    }

    if (c.x > b.x) return 0; // it+1
    return it-1;
}


void apply(Point a, Point b, ll it) {
    if (it == 0) maxy = min(maxy, b.y);
    if (it == 1) maxx = min(maxx, b.x);
    if (it == 2) miny = max(miny, b.y);
    if (it == 3) minx = max(minx, b.x);
}

ll initIt(Point a, Point b) {
    if (a.x == b.x) {
        if (a.y > b.y) return 1;
        return 3;
    }

    if (a.x < b.x) return 0;
    return 2;
}
ll T = 0;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N;
    while (cin>>N, N) {
        vector<Point> vp; vp.resize(N);
        for (int i=0; i<N; i++) cin >> vp[i].x >> vp[i].y;
        vp.push_back(vp[0]);
        ll it = initIt(vp[0], vp[1]);
        setup();

        for (int i=0; i<N; i++) {
            apply(vp[i], vp[i+1], it);
            if (i+1 != N) it = iterate(vp[i+1], vp[i+2], it);
        }

        cout << "Floor #" << ++T << '\n';
        if (maxx < minx || maxy < miny) {
            cout << "Surveillance is impossible.\n\n";
        }
        else {
            cout << "Surveillance is possible.\n\n";
        }
    }
}
