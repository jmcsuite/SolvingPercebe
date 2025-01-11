#include <bits/stdc++.h>
using namespace std;
using ll = int;
using pll = pair<ll,ll>;
using vll = vector<ll>;

const int maxn = 2e5;
/*
struct segmentTree {
    struct str {
        ll a;
        ll b;
        str() : a(1e17), b(-1 * 1e17) {}
        str(ll _a, ll _b) : a(_a), b(_b) {}
        str(ll _a) : a(_a), b(_b) {}
    };

    str func(str a, str b) {
        str c(min(a.a, b.a), max(a.b, b.b));
        return c;
    }

    str st[2*maxn];
    ll n;

    void build(vll& vl, int sizn) {
        n = sizn;
        for (int i=0; i<n; i++) st[i+n] = {vl[i], vl[i]};
        for (int i=n-1; i>0; i--) st[i] = func(st[i*2], st[i*2+1]);
    }

    // 0-indexed; value replace;
    void update(int pos, ll v) {
        str x(v);
        for(pos+=n, st[pos]=x,pos/=2; pos; pos/=2) {
            st[pos] = func(st[pos*2],st[pos*2+1]);
        }
    }

    str query(int l, int r) {
        str ansl={1e17, -1 * 1e17};
        str ansr={1e17, -1 * 1e17};
        for (l+=n,r+=n; l<r; l/=2,r/=2) {
            if (l%2) ansl=func(ansl, st[l++]);
            if (r%2) ansr=func(st[--r],ansr);
        }
        return func(ansl, ansr);
    }
};

segmentTree stSum;
segmentTree stRes;
*/
const int block = 447;
ll sSum[block];
ll sRes[block];
ll bAns[block];
ll cSum[block];
ll cRes[block];
ll sum[maxn];
ll res[maxn];
ll vl[maxn];
ll n,q;

void updateblock(ll x) {
    ll id = x/block;
    sum[x] = vl[x] + x;
    res[x] = vl[x] - x;

    ll b = id * block;
    ll e = min((id+1)*block, n);

    ll ans = 0;
    ll maxSum = sum[b];
    ll minRes = res[b];
    ll minSum = sum[b]; 
    ll maxRes = res[b];
    for (int i=b; i<e; i++) {
        ans = max(ans, maxSum - sum[i]);
        ans = max(ans, res[i] - minRes);
        minRes = min(minRes, res[i]);
        maxSum = max(maxSum, sum[i]);
        minSum = min(minSum, sum[i]);
        maxRes = max(maxRes, res[i]);
    }
    sSum[id] = maxSum;
    sRes[id] = maxRes;
    cSum[id] = minSum;
    cRes[id] = minRes;
    bAns[id] = ans;
}

ll calcAns() {
    ll ans = 0;
    for (int i=0; i<n; i+=block) {
        ll id = i / block; 
        ans = max(ans, bAns[id]);
    }
    ll maxSum = sSum[0];
    ll minRes = cRes[0];
    for (int i=block; i<n; i+=block) {
        ll id = i/block;
        ans = max(ans, maxSum - cSum[id]);
        ans = max(ans, sRes[id] - minRes);
        minRes = min(minRes, cRes[id]);
        maxSum = max(maxSum, sSum[id]);
    }
    return ans;
}

void solve() {
    cin>>n>>q;
    for (int i=0; i<n; i++) cin >> vl[i];

    for (int i=0; i<n; i++) sum[i] = vl[i] + i;
    for (int i=0; i<n; i++) res[i] = vl[i] - i;

    for (int i=0; i<n; i+=block) {
        updateblock(i);
    }

    cout << calcAns() << '\n';

    while (q--) {
        ll p,v;
        cin>>p>>v; 
        p--; 
        vl[p] = v;
        updateblock(p);
        ll ans = calcAns();
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while (T--) solve();
}
