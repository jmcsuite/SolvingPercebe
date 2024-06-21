#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 12;
ll vl[maxn];
ll ans = -1;

ll a, b;
void add(ll x) {
    if (x == maxn) {
        ll cc = 0;
        for (int i = 0; i < x; i++) cc = cc + vl[i];
        ans = max(ans, cc);
        if (cc >= 4) {
            cout << "Sol: "; 
            for (int i = 0; i < 12; i++) cout << vl[i] << ' ';
            cout << endl;
        }
        return;
    }

    vl[x] = a;
    if (x >= 4) {
        ll cc = 0;
        for (int i = x; i >= x-4; i--) cc = cc + vl[i];
        if (cc < 0) add(x+1);
    }
    else {
        add(x+1);
    }
    
    vl[x] = -1*b;
    if (x >= 4) {
        ll cc = 0;
        for (int i = x; i >= x-4; i--) cc = cc + vl[i];
        if (cc < 0) add(x+1);
    }
    else {
        add(x+1);
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (cin >> a >> b) {
        ans = -1;
        add(0);
        cout << (ans >= 0 ? to_string(ans) : "Deficit") << '\n';
    }
}
