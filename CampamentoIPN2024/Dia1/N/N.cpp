#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxl = 3e5+1;
const int maxn = 3e4+1;

typedef struct times {
    ll tslow;
    ll tfast;
    ll d;
    times(ll a, ll b, ll c) : tslow(a), tfast(b), d(c) {}
    times() : tslow(0), tfast(0), d(0) {}
} times;

times tt[maxn];
ll fastans[maxn];
ll ans[maxn];
ll qans[maxn];
ll sum[maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,Q; cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        cin >> tt[i].d >> tt[i].tfast >> tt[i].tslow;
    }
    sort(tt, tt + N, [](times& a, times& b) {
            return a.tslow > b.tslow;
            });
    ans[0] = tt[0].tslow;
    fastans[0] = tt[0].tfast;
    for (int i = 1; i < N; i++) {
        fastans[i] = max(tt[i].tfast, fastans[i-1]);
        ans[i] = max(tt[i].tslow, fastans[i-1]);
    }
    ans[N] = fastans[N-1];
    for (int i = N-1; i >= 0; i--) sum[i] = sum[i+1] + tt[i].d;
    ll totsum = sum[0];
    for (int i = 0; i <= N; i++) qans[i] = maxl;

    bitset<maxl> bs(1);
    bitset<maxl> bs2;
    for (int i = N; i >= 0; i--) {
        if (i < N) bs |= (bs << tt[i].d);

        //bs |= (bs << tt[j].d);

        /*
        for (int j = maxl-1, b = 0; j >= 0; j--, b++) {
            if (!bs.test(b)) continue;
            ll qq = max(totsum - sum[i] + b, totsum - b);
            qans[i] = min(qq, qans[i]);
        }
        */
        
        
        ll ss = sum[i];
        ll maxans = ss/2;
        bs2 = (bs << (maxl-maxans-1)) >> (maxl-maxans-1);

        ll x = 0; ll dis = maxans;
        while (dis > 0) {
            if (sum[i] - (x + dis) < (x + dis) || (bs2>>(x+dis)).none()) dis /= 2;
            else x += dis;
        }
        qans[i] = (totsum - x);
        
    }

    while (Q--) {
        ll q; cin >> q;
        ll x = -1;
        ll dis = maxn;
        while (dis > 0) {
            if (x + dis > N || qans[x+dis] > q) dis /= 2;
            else x += dis;
        }
        if (x == -1) cout << -1 << '\n';
        else cout << ans[x] << '\n';
    }
}
