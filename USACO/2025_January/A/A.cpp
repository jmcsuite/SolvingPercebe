#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;


const int maxn = 2e5+3;
ll c[maxn];
ll a[maxn];
ll med[maxn];
ll leq[maxn];
ll meq[maxn];
ll ans[maxn];
//ll vis[maxn];

ll n;
ll LEQ(ll x, ll q) {
    //if (vis[x]) return leq[x];
    if (x*2 < n) return leq[x];
    if (a[x] <= q) return 0;
    else return c[x];
}

ll MEQ(ll x, ll q) {
    //if (vis[x]) return meq[x];
    if (x*2 < n) return meq[x];
    if (a[x] >= q) return 0;
    else return c[x];
}

ll MED(ll x, ll q) {
    //if (vis[x]) return med[x];
    if (x*2 < n) return med[x];
    if (a[x] == q) return 0;
    else return c[x];
}


void update(ll x, ll q) {
    //for (ll x = n/2; x>=1; x/=2) vis[x]=1;
    for (; x>=1; x/=2) {
        if (2*x > n) continue;
        ll mleq = (a[x] <= q ? 0 : c[x]);
        ll mmeq = (a[x] >= q ? 0 : c[x]);
        ll mmed = (a[x] == q ? 0 : c[x]);

        leq[x] = min(mleq+LEQ(x*2,q), mleq+LEQ(x*2+1,q));
        leq[x] = min(leq[x], LEQ(x*2, q) + LEQ(x*2+1,q));

        meq[x] = min(mmeq+MEQ(x*2,q), mmeq+MEQ(x*2+1,q));
        meq[x] = min(meq[x], MEQ(x*2,q) + MEQ(x*2+1,q));

        med[x] = min(mmed + LEQ(x*2,q) + MEQ(x*2+1,q), mmed + MEQ(x*2,q) + LEQ(x*2+1, q)); 
        med[x] = min(med[x], MED(x*2,q) + mleq + MEQ(x*2+1,q));
        med[x] = min(med[x], MED(x*2,q) + mmeq + LEQ(x*2+1,q));

        med[x] = min(med[x], MED(x*2+1,q) + mleq + MEQ(x*2,q));
        med[x] = min(med[x], MED(x*2+1,q) + mmeq + LEQ(x*2,q));
    }
}

void solve(ll q) {
    //for (ll x = n/2; x>=1; x/=2) vis[x]=1;
    for (ll x = n; x>=1; x--) {
        if (2*x > n) continue;
        ll mleq = (a[x] <= q ? 0 : c[x]);
        ll mmeq = (a[x] >= q ? 0 : c[x]);
        ll mmed = (a[x] == q ? 0 : c[x]);

        leq[x] = min(mleq+LEQ(x*2,q), mleq+LEQ(x*2+1,q));
        leq[x] = min(leq[x], LEQ(x*2, q) + LEQ(x*2+1,q));

        meq[x] = min(mmeq+MEQ(x*2,q), mmeq+MEQ(x*2+1,q));
        meq[x] = min(meq[x], MEQ(x*2,q) + MEQ(x*2+1,q));

        med[x] = min(mmed + LEQ(x*2,q) + MEQ(x*2+1,q), mmed + MEQ(x*2,q) + LEQ(x*2+1, q)); 
        med[x] = min(med[x], MED(x*2,q) + mleq + MEQ(x*2+1,q));
        med[x] = min(med[x], MED(x*2,q) + mmeq + LEQ(x*2+1,q));

        med[x] = min(med[x], MED(x*2+1,q) + mleq + MEQ(x*2,q));
        med[x] = min(med[x], MED(x*2+1,q) + mmeq + LEQ(x*2,q));
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for (int i=1; i<=n; i++) cin>>a[i]>>c[i];
    solve(-1);
    ll Q; cin>>Q;
    vpll vq(Q);
    for (int i=0; i<Q; i++) {
        cin >> vq[i].first;
        vq[i].second = i;
    }
    sort(vq.begin(), vq.end());

    vpll vl;
    for (int i=1; i<=n; i++) vl.push_back({a[i], i});
    sort(vl.begin(), vl.end());

    ll i = 0; 
    ll j = 0;
    for (pll p: vq) {
        while (j < n && p.first >= vl[j].first) {
            update(vl[j].second, p.first);
            j++;
        }
        while(i < n && p.first > vl[i].first) {
            update(vl[i].second, p.first);
            i++;
        }
        ans[p.second] = MED(1,p.first);
    }

    for(i=0; i<Q; i++) cout << ans[i] << '\n';
}
