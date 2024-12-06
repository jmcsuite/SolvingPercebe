#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn = 10;
ll vl[maxn];

bool isCero() {
    for (int i = 1; i < maxn; i++) if (vl[i]) return false;
    if (vl[0] != 1) return false;
    return true;
}

int maxFreq() {
    ll tot = 0;
    vpll freq;
    for (int i = 0; i < maxn; i++) {
        tot += vl[i];
        freq.push_back({vl[i], i});
    }
    sort(freq.rbegin(), freq.rend()); 
    if (freq[0].first * 2 > tot + 1) return -2;
    if (freq[0].first * 2 < tot + 1) return -1;
    return freq[0].second;
}

int nextSmaller(int prev) {
    int ans = 9;
    for (int i = 9; i >= 0; i--) {
        if (vl[i] == 0) continue;
        if (i == prev) continue;
        ans = i;
    }
    return ans;
}

ll charCount() {
    ll x = 0;
    for (int i=0; i<maxn; i++) x+=vl[i];
    return x;
}

void solve() {
    for (int i = 0; i < maxn; i++) cin >> vl[i];
    if (isCero()) {
        cout << 0 << '\n';
        return;
    }

    ll prev = 0;
    while (charCount() != 0) {
        int mf = maxFreq();
        if (mf == prev || mf == -2) {
            cout << -1 << '\n';
            return;
        }

        if (mf != -1) {
            cout << mf;
            prev = mf;
            vl[mf]--;
            continue;
        }

        mf = nextSmaller(prev);
        cout << mf; 
        prev = mf;
        vl[prev]--;
    }
    cout << '\n';
    return;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) solve();
}
