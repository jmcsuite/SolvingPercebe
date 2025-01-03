#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int maxn = 2e5;

ll maxc(vll& v) {
    ll ans = 0;
    ll sum = 0;
    for (ll x: v) {
        sum += x;
        if (sum < 0) sum = 0;
        ans = max(sum, ans);
    }
    return ans;
}

void print(set<ll>& st) {
    cout << st.size() << '\n';
    for (ll x: st) cout << x << ' ';
    cout << '\n';
}


void solve() {
    ll N; cin>>N;
    vll vl(N);
    for (int i=0; i<N; i++) cin>>vl[i];
    ll id = -1;
    for (int i=0; i<N; i++) if(vl[i] != 1 && vl[i] != -1) id = i;

    vll a; 
    vll b;
    for (int i=0; i<id; i++) a.push_back(vl[i]);
    for (int i=id+1; i<N; i++) b.push_back(vl[i]);

    ll maxi = max(maxc(a), maxc(b));
    for (int i=0; i<(int)a.size(); i++) a[i] *= -1;
    for (int i=0; i<(int)b.size(); i++) b[i] *= -1;
    ll mini = max(maxc(a), maxc(b));
    mini *= -1;
    for (int i=0; i<(int)a.size(); i++) a[i] *= -1;
    for (int i=0; i<(int)b.size(); i++) b[i] *= -1;

    set<ll> st;
    for (int i=mini; i<=maxi; i++) st.insert(i);

    if (id == -1) {
        print(st); 
        return;
    }

    maxi = mini = 0;
    reverse(a.begin(), a.end());
    ll sum = 0; 
    for (ll x: b) {
        sum += x;
        maxi = max(maxi, sum);
        mini = min(mini, sum);
    }

    ll maxia, minia; 
    maxia = minia = 0;
    sum = 0;
    for (ll x: a) {
        sum += x;
        maxia = max(maxia, sum);
        minia = min(minia, sum);
    }
    maxi += maxia;
    mini += minia;
    ll delta = vl[id];
    for (int i=mini+delta; i<=maxi+delta; i++) st.insert(i);
    print(st);
    return;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while (T--) solve();
}
