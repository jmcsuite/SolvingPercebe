#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    string s,t; cin>>s>>t;
    ll n = s.size();

    ll pr = 0;
    vector<ll> a;
    vector<ll> b;

    for (int i=0; i<n; i++) {
        if (s[i] == s[pr]) continue;
        a.push_back(i - pr);
        pr = i;
    }
    a.push_back(n-pr);

    pr = 0;
    for (int i=0; i<n; i++) {
        if (t[i] == t[pr]) continue;
        b.push_back(i-pr);
        pr= i;
    }
    b.push_back(n-pr);


    ll ans = 0;
    ll i = 0;
    ll j = 1;
    if (s[0] != t[0]) {
        if (a.size() == 1) {
            cout << -1 << '\n';
            return;
        }
        i = 1; 
        j = 2; 
        if (a.size() <= 2) a.push_back(0);
        a[2] += a[0];
        ans++;
    }
    ll k = 0;

    while (k < (int)b.size()) {
        if (a[i]  > b[k]) {
            cout << -1 << '\n';
            return;
        }
        if (a[i] == b[k]) {
            i+=2;
            k++; 
            swap(i,j);
            continue;
        }
        if (i + 2 >= (int)a.size()) {
            cout << -1 << '\n';
            return;
        }
        a[i+2] += a[i];
        if (j + 2 >= (int)a.size()) a.push_back(0);
        a[j+2] += a[j];
        i += 2;
        j += 2;
        ans++;
    }
    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while(t--) solve();
}
