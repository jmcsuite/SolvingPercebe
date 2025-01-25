#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 2e5;
ll a[maxn], b[maxn];

void solve() {
    ll A,B; cin>>A>>B;
    for (int i=0; i<A; i++) cin>>a[i];
    for (int i=0; i<B; i++) cin>>b[i];
    sort(a, a+A);
    sort(b, b+B);

    vll u,v;
    for (int i=0, j=A-1; i<j; i++,j--) u.push_back(a[j] - a[i]);
    for (int i=0, j=B-1; i<j; i++,j--) v.push_back(b[j] - b[i]);

    vll ans;
    ll sum = 0;

    ll x = 0;
    ll y = 0;
    
    for (int i=1; i<=A; i++) {
        ll mink = 0;
        ll maxk = i;

        mink = max(mink, 2*i - A);
        maxk = min(maxk, B-i);
        if (mink > maxk) break;

        if (x >= (int)u.size()) sum += v[y++];
        else if (y >= (int)v.size()) sum += u[x++];
        else sum += (u[x] > v[y] ? u[x++] : v[y++]);

        while (y < mink) {
            sum -= u[--x];
            sum += v[y++];
        }

        while (y > maxk) {
            sum -= v[--y];
            sum += u[x++];
        }
        ans.push_back(sum);
    }
    cout << ans.size() << '\n';
    for (ll x: ans) cout << x << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while (T--) solve();
}
