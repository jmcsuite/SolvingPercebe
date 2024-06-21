#include <bits/stdc++.h>
using namespace std;
using ll = long long;


ll cost(ll w) {
    if (w <= 100) return w*2;
    ll ans = 100 * 2;
    if (w <= 10000) return ( (w-100) * 3 + ans);
    ans += (10000 - 100) * 3;
    if (w <= 1000000) return ((w-10000) * 5 + ans);
    ans += (1000000-10000) * 5;
    return ((w-1000000) * 7 + ans);
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll A, B;
    while (cin >> A >> B, A || B) {
        ll en = 0;
        ll dis = A + 1;
        while (dis) {
            if (cost(en+dis) <= A) en+=dis;
            else dis/=2;
        }

        ll my = 0;
        dis = en;
        while (dis) {
            if (my + dis <= en && ((my+dis) <= (en) - (my+dis)) && (cost(en - my - dis) - cost(my + dis) >= B)) my += dis;
            else dis/=2;
        }
        cout << cost(my) << '\n';
        //cout << my << ' ' << cost(my) << ' ' << en << ' ' << cost(en-my) << '\n';
    }
}
