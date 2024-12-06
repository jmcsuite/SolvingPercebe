#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace CH {

    struct Frac { 
        ll num, den;
        Frac() : num(0), den(1) {}
        Frac(ll a, ll b) : num(a), den(b) {}
        Frac(ll a) : num(a), den(1) {}
        bool operator==(const Frac& b) const {
            return num * b.den == b.num * den;
        }
        bool operator==(int b) const {
            return *this==Frac(b);
        }
        bool operator<(const Frac& b) const {
            return (num * b.den) < (b.num * den);
        }
        bool operator<=(const Frac& b) const {
            return (num * b.den) <= (b.num * den);
        }
        bool operator>=(const Frac& b) const {
            return (num * b.den) >= (b.num * den);
        }
        bool operator<(int b) const {
            return *this<Frac(b);
        }
        Frac operator-(const Frac& b) const {
            if (den == b.den) return {num - b.num, den};
            return {num*b.den - b.num*den, den*b.den};
        }
        Frac operator*(const Frac& b) const {
            return {num*b.num, den*b.den};
        }
    };
        

    struct Point {
        Frac x,y;
        Point() : x(0), y(0) {}
        Point(ll _x, ll _y) : x(_x), y(_y) {}
        Point(Frac _x, Frac _y) : x(_x), y(_y) {}
        Frac operator*(const Point& b) const {
            return x * b.y - y*b.x;
        }
        Point operator-(const Point& b) const {
            return {x-b.x, y-b.y};
        }
        bool operator<(const Point& b) const {
            if (x != b.x) return x < b.x;
            return y < b.y;
        }
        bool operator==(Point& b) const {
            return (x == b.x && y == b.y);
        }
    };

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
        //for (size_t i = 1; i+1 < ch2.size(); i++) ch.push_back(ch2[i]);
        return ch;
    }

    bool inConvexHull(set<Point>& ch, Point& p) {
        auto it = ch.lower_bound(p);
        if (it == ch.end()) return false;
        if (*it == p) return true;
        if (it == ch.begin()) return true;
        auto p1 = *it;
        auto p2 = *(--it);
        if (p2.x == p1.x) return true;
        if ((p-p2) * (p1-p2) >= 0) return true;
        return false;
    } 

    void addPointConvexHull(set<Point>& ch, Point& p) {
        if (inConvexHull(ch, p)) return;
        auto it = ch.insert(p).first;
        auto it2 = (--it); 
        ++it;
        while (it2 != ch.begin()) {
            auto it3 = --it2;
            ++it2;
            Point p = *it;
            Point p2 = *it2;
            Point p3 = *it3;
            if ((p2 - p3) * (p - p3) < 0) break;
            ch.erase(it2);
            it2 = it3;
        }

        if (it == ch.end()) return;
        it2 = (++it);
        --it;

        while (it2 != ch.end()) {
            auto it3 = ++it2;
            --it2;
            if (it3 == ch.end()) return;
            Point p = *it;
            Point p2 = *it2;
            Point p3 = *it3;
            if ((p2-p) * (p3-p) < 0) break;
            ch.erase(it2);
            it2 = it3;
        }
    }
}



int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    vector<CH::Point> vl(N);
    for (int i = 0; i < N; i++) cin >> vl[i].x.num >> vl[i].y.num;
    //for (

    ll Q; cin >> Q;
    vector<bool> rm(N);
    vector<pair<ll, pair<ll, CH::Point>>> q(Q);
    for (int i = 0; i < Q; i++) {
        char c; cin >> c;
        if (c == 'q') {
            ll x; cin >> x; x--;
            rm[x] = 1;
            q[i].first = 1; 
            q[i].second.first = x;
            continue;
        }
        ll t, x, y; cin >> t >> x >> y;
        //x/=t; y/=t;
        q[i].first = 2;
        q[i].second.second.x = {x,t};
        q[i].second.second.y = {y,t};
        //q[i].second.second = {x,y};
    }

    reverse(q.begin(), q.end());
    vector<CH::Point> ch; 
    ll maxy = 0;
    for (int i = 0; i < N; i++) {
        if (rm[i]) continue;
        ch.push_back(vl[i]);
        maxy = max(vl[i].y.num, maxy);
    }
    ch.push_back({0,maxy});
    ch.push_back({0,0});
    auto tt = CH::getConvexHull(ch);
    set<CH::Point> st(tt.begin(), tt.end());

    vector<bool> ans;
    for (int i = 0; i < Q; i++) {
        if (q[i].first == 1) {
            CH::addPointConvexHull(st, vl[q[i].second.first]);
            CH::Point ppp(0,vl[q[i].second.first].y);
            CH::addPointConvexHull(st, ppp);
            continue;
        }
        ans.push_back(CH::inConvexHull(st, q[i].second.second));
    }
    reverse(ans.begin(), ans.end());
    for (bool x : ans) cout << (x ? "no" : "yes") << '\n';
}
