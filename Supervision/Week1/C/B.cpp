#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 50000;
const int length = 300;
const int maxb = maxn/length + 1;



ll block_prefix[maxb];
ll block_suffix[maxb];
ll block_ans[maxb];
ll block_sum[maxb];
ll vl[maxn];

ll N;
void update(ll x) {
    ll i = x*length;
    ll ans = vl[i];
    ll current = ans;
    for (++i; i < (x+1)*length && i<N; i++) {
        if (current < 0) current = 0;
        current += vl[i];
        if (current > ans) ans = current;
    }
    block_ans[x] = ans;

    i = x*length;
    ans = vl[i];
    current = ans;
    for (++i; i < (x+1)*length && i<N; i++) {
        current += vl[i];
        if (current > ans) ans = current;
    }
    block_prefix[x] = ans;

    ans = current;
    i = x*length;
    for (; i<(x+1)*length && i<N; i++) {
        if (current > ans) ans = current;
        current -= vl[i];
    }
    block_suffix[x] = ans;

    i = x*length;
    ans = 0;
    for (; i<(x+1)*length && i<N; i++) {
        ans += vl[i];
    }
    block_sum[x] = ans;

}

ll manualQuery(ll a, ll b) {
    ll ans = vl[a];
    ll current = vl[a];
    for (int i = a+1; i < b; i++) {
        if (current < 0) current = 0;
        current += vl[i];
        if (current > ans) ans = current;
    }
    return ans;
}

ll query(ll a, ll b) {
    if (b - a <= length) return manualQuery(a, b);
    ll ans = vl[a];
    ll current = vl[a];
    ll fblock = ((a/length) + 1);

    for (int i = a+1; i < fblock*length; i++) { //
        if (current < 0) current = 0;
        current += vl[i];
        if (current > ans) ans = current;
    }

    ll lblock = ((b/length));
    for (int i = fblock; i < lblock; i++) {
        ans = max(ans, block_ans[i]);
        ans = max(ans, block_prefix[i] + current);
        current = max(current + block_sum[i], block_suffix[i]);
    }

    for (int i = lblock*length; i < b; i++) {
        if (current < 0) current = 0;
        current += vl[i]; 
        if (current > ans) ans = current;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N;
    for (int i=0; i<N; i++) cin >> vl[i];
    for (int i=0; i<N; i+=length) update(i/length);
    ll M; cin>>M;
    while (M--) {
        ll q,a,b; cin >> q >> a >> b; a--;
        if (q==1) {
            cout << query(a,b) << '\n';
            continue;
        }
        vl[a]=b;
        update(a/length);
    }
}
