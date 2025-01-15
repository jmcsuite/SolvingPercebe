#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using vll = vector<ll>;

void solve() {
    ll n; cin>>n;
    vll a(n);
    vll b(n);
    vll vl(n);
    for (int i=0; i<n; i++) cin>>a[i];
    for (int i=0; i<n; i++) cin>>b[i];
    for (int i=0; i<n; i++) vl[i] = a[i] - b[i];

    ll ccneg = 0;
    ll mini = max(vl[0], vl[n-1]);
    for (int i=0; i<n; i++) {
        if (vl[i] < 0) ccneg++;
        else mini = min(mini, vl[i]);
    }
    if (ccneg == 0) {
        cout << "YES\n"; return;
    }

    if (ccneg > 1) {
        cout << "NO\n"; return;
    }

    for (int i=0; i<n; i++) {
        if (vl[i] < 0) ccneg = vl[i] * -1;
    }

    if (ccneg > mini) {
        cout << "NO\n";
        return;
    }
    else {
        cout << "YES\n";
        return;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--) solve();
}
