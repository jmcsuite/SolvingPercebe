#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

bool winsFirst(ll gb, ll x) {
    return ((gb + x)%2 == 1);
}

using pp = pair<char, int>;

map<pp, int> mp;

void playFirst(set<pp>& ga, set<pp>& gb, set<pp>& gc) {
    while (1) {
        if (ga.empty() && gb.empty() && gc.empty()) return;
        if (!ga.empty()) {
            auto a = ga.begin();
            cout << a->first << ' ' << a->second << endl;
            ga.erase(a);
        } else if (!gb.empty()) {
            auto a = gb.begin();
            cout << a->first << ' ' << a->second << endl;
            gb.erase(a);
        }
        else {
            auto a = gc.begin();
            cout << a->first << ' ' << a->second << endl;
            gc.erase(a);
        }

        if (ga.empty() && gb.empty() && gc.empty()) return;
        pp q; cin >> q.first >> q.second;
        int id = mp[q];
        if (id == 1) gb.erase(q);
        else gc.erase(q);
    }
}

void playSecond(set<pp>& ga, set<pp>& gb, set<pp>& gc) {
    while (1) {
        if (ga.empty() && gb.empty() && gc.empty()) return;
        pp q; cin >> q.first >> q.second;
        int id = mp[q];
        if (id == 0) ga.erase(q);
        else if (id == 1) gb.erase(q);
        else gc.erase(q);

        if (ga.empty() && gb.empty() && gc.empty()) return;
        if (gb.size() % 2 == 1) {
            auto a = gb.begin();
            cout << a->first << ' ' << a->second << endl;
            gb.erase(a);
        } else if (!ga.empty()) {
            auto a = ga.begin();
            cout << a->first << ' ' << a->second << endl;
            ga.erase(a);
        } else if (!gc.empty()) {
            auto a = gc.begin();
            cout << a->first << ' ' << a->second << endl;
            gc.erase(a);
        }
        else {
            auto a = gb.begin();
            cout << a->first << ' ' << a->second << endl;
            gb.erase(a);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    set<pp> ga, gb, gc;
    for (int i = 0; i < N; i++) {
        pp x; cin >> x.first >> x.second;
        if (x.first == '*' && ((x.second%2) == 0)) {
            mp[x] = 0;
            ga.insert(x);
        } else if (x.first == '+' && ((x.second%2) == 1)) {
            mp[x] = 1;
            gb.insert(x);
        } else {
            mp[x] = 2;
            gc.insert(x);
        }
    }
    int y; cin >> y;
    if (ga.empty() && winsFirst(gb.size(), y)) {
        cout << "me" << endl;
        playFirst(ga, gb, gc);
        return 0;
    }
    if (ga.size() == 1 && winsFirst(gb.size(), 0)) {
        cout << "me" << endl;
        playFirst(ga, gb, gc);
        return 0;
    }
    cout << "you" << endl;
    playSecond(ga, gb, gc);
}
