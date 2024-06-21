#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e7;

ll vl[maxn];
ll N;

bool check(ll k) {
    ll p = 0;
    for (int i = 0; i < N; i++) {
        if (p + k < vl[i]) return false;
        if (p + k > vl[i]) {
            p = vl[i];
            continue;
        }
        p = vl[i];
        k--;
    }
    return true;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    ll Q = 0;
    while (T--) {
        cin >> N; 
        for (int i = 0; i < N; i++) cin >> vl[i];
        
        ll ans = maxn;
        ll dis = ans / 2;
        while (dis) {
            if (ans - dis >= 0 && check(ans-dis)) ans-=dis;
            else dis/=2;
        }
        cout << "Case " << ++Q << ": " << ans << '\n';
    }
}
