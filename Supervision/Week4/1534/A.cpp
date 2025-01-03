#include <bits/stdc++.h>
using namespace std;
using ll = long long;


ll W,L,N;


ll win() {
    ll matches = min(N-1, W); 
    ll ans = matches * 3 + (N-1 - matches)*1;

    if (W-matches > L) ans += 3;
    else if (W - matches == L) ans += 1;
    return ans;
}

ll lose() {
    ll points = N * 3;

    ll ans = (N-1)*2;
    // calc 1
    ll draws = min(N-1, L); 
    ans += draws;

    // calc 2;
    ll a2 = N*2;
    if (W > L) return points - ans;
    ll d2 = min(N, L-W);
    a2 += d2;
    return min(points-ans, points-a2);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>W>>L>>N;
    cout << win() << ' ' << lose() << '\n';
}
