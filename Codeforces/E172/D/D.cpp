#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
struct v {
    ll l;
    ll r;
    ll q;
    v() : l(0), r(0), q(0) {}
    v(ll a, ll b, ll c) : l(a), r(b), q(c) {}
    bool operator<(const v& other) const {
        if (r == other.r) return l < other.l;
        return r > other.r;
    }
};
const int maxn=2e5;

ll ans[maxn];
v vl[maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while (T--) {
        ll N; cin>>N;
        for (ll i=0; i<N; i++) {
            cin>>vl[i].l>>vl[i].r;
            vl[i].q=i;
        }
        sort(vl, vl+N);
        ans[vl[0].q] = 0;
        set<ll> st; 
        st.insert(vl[0].l);

        for (ll i=1; i<N; i++) {
            if ((i < N-1) && (vl[i+1].r == vl[i].r) && (vl[i+1].l == vl[i].l)) {
                ans[vl[i].q] = 0;
            } 
            else if (st.upper_bound(vl[i].l) == st.begin()) {
                ans[vl[i].q] = 0;
            }
            else {
                auto it = st.upper_bound(vl[i].l); --it;
                ll diffl = vl[i].l - *it;
                ans[vl[i].q] = diffl;
            }

            st.insert(vl[i].l);
        }

        st.clear();
        sort(vl, vl+N, [&](v& a, v& b) {
                if (a.l != b.l) return a.l < b.l;
                return a.r > b.r;
                });

        ans[vl[0].q] = 0;
        st.insert(vl[0].r);
        for (ll i=1; i<N; i++) {
            if ((i < N-1) && (vl[i+1].r == vl[i].r) && (vl[i+1].l == vl[i].l)) {
                ans[vl[i].q] = 0;
            }
            else if (st.lower_bound(vl[i].r) == st.end()) {
                ans[vl[i].q] = 0;
            }
            else {
                auto it = st.lower_bound(vl[i].r);
                ll diffr = *it - vl[i].r;
                ans[vl[i].q] += diffr;
            }
            st.insert(vl[i].r);
        }


        for (int i=0; i<N; i++) cout << ans[i] << '\n';
    }
}
