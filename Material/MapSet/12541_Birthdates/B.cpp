#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

const int maxn = 100;
struct p {
    ll d;
    ll a;
    ll m;
    string n;
};

p vl[maxn];

bool f(p& a, p& b) {
    if (a.a != b.a) return a.a > b.a;
    if (a.m != b.m) return a.m > b.m;
    return a.d > b.d;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> vl[i].n >> vl[i].d >> vl[i].m >> vl[i].a;
    }
    sort (vl, vl + N, f);
    cout << vl[0].n << '\n';
    cout << vl[N-1].n << '\n';
}
