#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using pll = pair<ll,ll>;

vector<pair<ll,pll>> in;

ll d, l, c;
double t, m;
const double EPS = 1e-9;

void init(double x) {
    t = m = x;
    l = 0;
    d = 0;
    c = in[0].second.second;
}

bool apply(int i) {
    double dis = (in[i].second.first - d);
    t = t - dis* (double(c) / 100.00) - double(l*(in[i].second.first - d));
    d = in[i].second.first;

    //cout << i << ' ' << t << '\n';
    if (t + EPS < 0) return false;
    switch (in[i].first) {
        case 0: 
            c = in[i].second.second;
            return true;
        case 1:
            l++;
            return true;
        case 2:
            t = m;
            return true;
        case 3:
            l = 0;
            return true;
        case 4:
            return true;
        default:
            return false;
    }
}

bool check(double x) {
    init(x);
    for (int i = 1; i < (int)in.size(); i++) {
        if (!apply(i)) return false;
    }
    return true;
}
const double b_eps = 1e-9;
double search() {
    double init = 1e9;
    double dis = init/2;

    for (int i = 0; i < 150; i++) {
        if (dis < b_eps) break;
        if (init - dis > 0 && check(init-dis)) init -= dis;
        else dis /= 2;
    }
    return init;
}

void read_input() {
    in.clear();
    while (true) {
        int a; cin >> a;
        string b; cin >> b;
        if (b == "Goal") {
            in.push_back({4, {a,0}});
            return;
        }
        if (b == "Mechanic") {
            in.push_back({3, {a,0}});
            continue;
        }
        if (b == "Leak") {
            in.push_back({1, {a,0}});
            continue;
        }
        
        if (b == "Gas") {
            string c; cin >> c;
            in.push_back({2, {a,0}});
            continue;
        }

        string c; cin >> c;
        int d; cin >> d;
        if (d == 0) return;
        in.push_back({0,{a,d}});
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        read_input();
        if (in.empty()) return 0;
        cout << fixed << setprecision(3) << search() << '\n';
    }
}

