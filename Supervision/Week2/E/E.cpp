#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 1e5;

struct segmentTree {
    using str = long long;

    str func(str u, str v) {
        return max(u,v);
    }

    str st[2*maxn];

    ll n;

    void build(vll& vl, int sizn) {
        n = sizn;
        for(int i=0; i<n; i++) st[i+n] = vl[i];
        for(int i=n-1; i>0; i--) st[i] = func(st[i*2], st[i*2+1]);
    }

    str query(int l, int r) {
        str ansl=0;
        str ansr=0;
        for(l+=n, r+=n; l<r; l/=2,r/=2) {
            if(l%2) ansl=func(ansl, st[l++]);
            if(r%2) ansr=func(st[--r], ansr);
        }
        return func(ansl, ansr);
    }
};

ll vl[maxn];
ll gb[maxn];
ll ge[maxn];
ll g[maxn];
ll sz[maxn];
ll cantg;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N;
    segmentTree st;
    while (cin>>N, N) {
        ll Q; cin>>Q;
        for (int i=0; i<N; i++) cin>>vl[i];
        cantg=0; gb[0]=0; g[0]=0;
        for (int i=0; i<N; i++) {
            if (i>0 && (vl[i] != vl[i-1])) {
                ge[cantg]=i;
                ++cantg;
                gb[cantg]=i;
                sz[cantg]=0;
            }
            sz[cantg]++;
            g[i]=cantg;
        }
        ge[cantg]=N;
        cantg++;

        vector<ll> freq;
        for (int i=0; i<cantg; i++) freq.push_back(sz[i]);
        st.build(freq, cantg);

        while (Q--) {
            ll i, j; cin>>i>>j; --i; --j;

            ll ans = st.query(g[i]+1, g[j]);
            ll a = min(j+1, ge[g[i]]) - i;
            ll b = j+1 - max(gb[g[j]],i);
            ans = max(ans, a);
            ans = max(ans, b);
            cout << ans << '\n';
        }
    }
}
