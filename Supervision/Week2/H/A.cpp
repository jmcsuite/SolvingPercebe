#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

vector<int> z_func(vll& a) {
    vector<int> z(a.size(),0);
    for(int i=1,l=0,r=0; i<(int)a.size(); ++i) {
        if(i<=r) z[i]=min(r-i+1,z[i-l]);
        while(z[i]+i<(int)a.size() && a[z[i]]==a[z[i]+i]) z[i]++;
        if(i+z[i]-1>r) l=i, r=z[i]+i-1;
    }
    return z;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin >> N >> M;
    vll vl(N); 
    for (int i=0; i<N; i++) cin >> vl[i];
    sort(vl.begin(), vl.end());

    vll dif(N);
    for (ll i=0; i<N-1; i++) dif[i] = vl[i+1]-vl[i];
    dif[N-1] = ((vl[0]-vl[N-1])%M + M)%M;

    vll toz;

    for (ll i=N-1; i>=0; i--) toz.push_back(dif[i]);
    toz.push_back(-1);
    for (ll i=0; i<N; i++) toz.push_back(dif[i]);
    for (ll i=0; i<N-1; i++) toz.push_back(dif[i]);

    auto z = z_func(toz);
    set<ll> ans;

    for (ll i=N+1; i<(int)z.size(); i++) {
        if (z[i] == N) ans.insert((vl[i%N]+vl[N-1])%M);
    }

    cout << ans.size() << '\n';
    if (ans.size() == 0) return 0;
    for (ll x: ans) cout << x << ' ';
    cout << '\n';
}
