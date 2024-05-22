#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6;
ll vl[maxn];
int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    set<ll> st;
    for (int i = 0; i < N; i++) {
        ll x; cin >> x; x--;
        vl[x] = 1;
    }

    ll cc = 0;
    int last = 0;
    for (int i = 0; i < maxn; i++) if(vl[i]) last = i;
    for (int i = 0; i < last; i++) {
        if(!vl[i]) break;
        cc++;
    }
    cout << (cc%2 ? "Bobius\n" : "Alicius\n");
}

