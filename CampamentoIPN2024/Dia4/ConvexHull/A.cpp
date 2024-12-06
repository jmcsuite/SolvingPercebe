#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

namespace CH {
    struct Point {
        ll x;
        ll y;
        Point() : x(0), y(0) {}
        Point(ll _x, ll _y) : x(_x), y(_y) {}
        ll operator*(const Point& b) const {
            return x * b.y - y*b.x;
        }
        Point operator-(const Point& b) const {
            return {x-b.x, y-b.y};
        }
        bool operator==(const Point& b) const{
            return ((x == b.x) && (y == b.y));
        }

        bool operator<(Point& b) {
            if (x != b.x) return x < b.x;
            return y < b.y;
        }
    };

    // skips colineal
    vector<Point> partialConvex(const vector<Point>& vl) {
        if (vl.size() == 0) return {};
        vector<Point> c(vl.size());
        c[0] = vl[0];
        int j = 1; 
        for (size_t i = 1; i < vl.size(); i++) {
            if (vl[i] == c[j-1]) continue;
            if (j == 1) {
                c[j++] = vl[i];
                continue;
            }
            if (vl[i] == c[j-2]) continue;
            if ((c[j-1]-c[j-2]) * (vl[i]-c[j-2]) < 0) {
                c[j++] = vl[i];
                continue;
            }
            j--; i--;
        }
        c.resize(j); 
        return c;
    }


    
    vector<Point> getConvexHull(vector<Point>& vl) {
        if (vl.size() == 0) return {};
        sort(vl.begin(), vl.end());
        auto ch1 = partialConvex(vl);
        reverse(vl.begin(), vl.end());
        auto ch2 = partialConvex(vl);
        vector<Point> ch;
        for (auto p : ch1) ch.push_back(p);
        for (size_t i = 1; i+1 < ch2.size(); i++) ch.push_back(ch2[i]);
        return ch;
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N;
    while (cin >> N, N) {
        vector<CH::Point> vl;
        for (int i = 0; i < N; i++) {
            ll x, y; cin >> x >> y;
            vl.push_back({x,y});
        }
        auto ch = CH::getConvexHull(vl);
        reverse(ch.begin(), ch.end());
        cout << ch.size() << '\n';
        for (auto p : ch) {
            cout << p.x << ' ' << p.y << '\n';
        }
    }
}

