#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 3e6;

struct segmentTree {
    typedef long long str;
    str func(str a, str b) {
        return min(a,b);
    }

    str st[2*maxn];
    ll n;
    void build(int sizn) {
        n = sizn;
        for (int i=0; i<n; i++) st[i+n] = n;
        for (int i=n-1; i>0; i--) st[i] = func(st[i*2], st[i*2+1]);
    }

    void update(int pos, str x) {
        for (pos+=n,st[pos]=x,pos/=2; pos; pos/=2) {
            st[pos] = func(st[pos*2], st[pos*2+1]);
        }
    }

    str query(int l, int r) {
        str ans = n;
        for (l+=n,r+=n;l<r;l/=2,r/=2) {
            if (l%2) ans = func(ans,st[l++]);
            if (r%2) ans = func(ans,st[--r]);
        }
        return ans;
    }
};

segmentTree st;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string s; cin>>s;
    ll n = s.size();
    vll ans(n);
    map<char,ll> mp;

    st.build(n);
    for (int i=n-1; i>=0; i--) {
        if (mp.find(s[i]) == mp.end()) ans[i]=1;
        else ans[i] = st.query(i+1, mp[s[i]]) + 1;
        st.update(i, ans[i]);
        mp[s[i]] = i+1;
    }
    ll x = 0;
    for (int i=0; i<n; i++) x = max(x, ans[i]);
    cout << x << '\n';
}
