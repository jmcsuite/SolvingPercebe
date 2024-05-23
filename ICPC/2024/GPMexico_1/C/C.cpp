#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll A,B,C; 
    cin >> A >> B >> C;
    vll vl(3);
    for (int i = 0; i < 3; i++) cin>>vl[i];
    sort(vl.begin(), vl.end());
    ll ans = 0;
    do {
        ll a = A/vl[0];
        ll b = B/vl[1];
        ll c = C/vl[2];
        ans = max(ans, a*b*c);
    }
    while (std::next_permutation(vl.begin(), vl.end()));
    cout << ans << '\n';
}

