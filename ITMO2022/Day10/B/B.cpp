#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn = 4e5 + 4;
namespace suffix {
    ll p[maxn], c[maxn], np[maxn], nc[maxn], cfreq[maxn], lcp[maxn];
    ll n;

    void pro(ll h) {
        // get cyclic shift order of size (1<<(h+1));
        for (int i=0; i<n; i++) {
            np[i] = p[i] - (1<<h);
            if (np[i] < 0) np[i] += n;
        }
        for (int i=0; i<n; i++) cfreq[i]=0;
        for (int i=0; i<n; i++) cfreq[c[i]]++;
        for (int i=1; i<n; i++) cfreq[i] += cfreq[i-1];

        for (int i=n-1; i>=0; i--) p[--cfreq[c[np[i]]]] = np[i];

        nc[p[0]] = 0;
        for (int i=1; i<n; i++) {
            ll a = p[i] + (1<<h);
            ll b = p[i-1] + (1<<h);
            if (a >= n) a -= n;
            if (b >= n) b -= n;
            nc[p[i]] = nc[p[i-1]];
            if (c[p[i]] != c[p[i-1]] || c[a] != c[b]) nc[p[i]]++;
        }
        for (int i=0; i<n; i++) c[i] = nc[i];
    }

    void pre(string s) {
        vector<pll> vp(n);
        for (int i=0; i<n; i++) vp[i] = {s[i], i};
        sort(vp.begin(), vp.end());
        for (int i=0; i<n; i++) p[i] = vp[i].second;

        c[vp[0].second] = 0;
        for (int i=1; i<n; i++) {
            c[vp[i].second] = c[vp[i-1].second];
            if (vp[i-1].first != vp[i].first) c[vp[i].second]++;
        }
    }

    void lcp_build(string s) {
        ll k = 0;
        for (int i=0; i<n; i++) {
            if (c[i] == n-1) {
                k=0;
                continue;
            }
            ll j = p[c[i]+1];
            for (;i+k < n && j+k < n && s[i+k] == s[j+k]; k++) ;
            lcp[c[i]] = k;
            k--;
            if (k < 0) k=0;
        }
    }

    // call this
    // dont forget to append a character 0 to s. 
    void build(string s) {
        n = s.size();
        pre(s);
        for (ll h=0; (1<<h) < n; h++) pro(h);
        lcp_build(s);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s; cin>>s; s.push_back(0);
    ll n = s.size();
    string t; cin>>t; t.push_back(1);
    s += t;

    suffix::build(s);
    ll ans = 0;
    ll ansi = 0;
    for (int i=0; i+1 < (int)s.size(); i++) {
        if ((suffix::p[i] >= n && suffix::p[i+1] < n) || (suffix::p[i] < n && suffix::p[i+1] >= n)) {
            if (ans < suffix::lcp[i]) {
                ans = suffix::lcp[i];
                ansi = suffix::p[i];
            }
        }
    }
    for (int i=ansi; i<ansi+ans; i++) cout << s[i];
    cout << '\n';
}