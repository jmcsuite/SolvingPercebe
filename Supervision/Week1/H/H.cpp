#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

using set_t = tree<ll,null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;

const int maxn = 200000;

ll a[maxn];
ll b[maxn];
ll vl[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    for (int i=0; i<N; i++) cin >> a[i];
    for (int i=0; i<N; i++) cin >> b[i];

    set_t st;
    for (int i=0; i<N; i++) {
        st.insert(a[i]);
        a[i] = a[i]-st.order_of_key(a[i]);
    }

    st.clear();
    for (int i=0; i<N; i++) {
        st.insert(b[i]);
        b[i] = b[i]-st.order_of_key(b[i]);
    }

    for (int i=N-1; i>=0; i--) {
        ll x = N-i;
        ll res = (a[i] + b[i]) / x;
        if (i > 0) a[i-1] += res;
        a[i] = (a[i] + b[i]) % x;
    }

    for (int i=0; i<N; i++) {
        vl[i] = *st.find_by_order(a[i]);
        st.erase(st.find_by_order(a[i]));
    }

    for (int i=0; i<N; i++) cout << vl[i] << (i+1==N ? '\n' : ' ');
}
