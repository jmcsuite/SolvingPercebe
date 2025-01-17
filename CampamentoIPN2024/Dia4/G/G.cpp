#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct slope {
    ll m, a, i;
    ll eval(ll x) {
        return x*m + a;
    }
};

struct cht {
    // gets minimum;
    // increasing queries
    // non-increasing (decreasing) slopes
    deque<slope> dq;

    // does b intersect base before a?
    bool remove(slope base, slope a, slope b) {
        ll deltaa = (base.a - a.a) * (b.m - base.m);
        ll deltab = (base.a - b.a) * (a.m - base.m);
        return deltaa >= deltab;
    }
    
    void add(slope x) {
        if (dq.empty()) {
            dq.push_back(x);
            return;
        }

        // slope could be the same
        if (dq.size() == 1) {
            if (dq.back().m != x.m) {
                dq.push_back(x);
                return;
            }
            slope a = dq.back(); 
            dq.pop_back();
            if (a.a < x.a) dq.push_back(a);
            else dq.push_back(x);
            return;
        }

        slope a = dq.back(); 
        dq.pop_back();
        slope base = dq.back();
        while (remove(base, a, x)) {
            a = base;
            dq.pop_back();
            if (dq.empty()) break;
            base = dq.back();
        }
        dq.push_back(a);


        //slope could be the same
        if (x.m != a.m) dq.push_back(x);
    }

    ll getmin(ll x, ll j) {
        while (dq.front().i <= j) dq.pop_front();
        if (dq.size() == 1) return dq.front().eval(x);

        slope a = dq.front();
        dq.pop_front();
        slope b = dq.front();
        while (b.eval(x) <= a.eval(x)) {
            a = b;
            dq.pop_front();
            if (dq.empty()) break;
            b = dq.front();
        }
        dq.push_front(a);
        return dq.front().eval(x);
    }
};

cht st;
const int maxn=1e5;

ll dp[maxn];
ll t[maxn];
ll sum[maxn];
void calc_dp(ll n) {
    for (int i=0; i<n; i++) {
        dp[i] = st.getmin(i, i);
        if (i > 0) dp[i] += sum[i-1];
    }
}

void add_st(ll n) {
    st.dq.clear();
    for (int i=1; i<n; i++) {
        //if (t[i] <= 0) continue;
        st.add({t[i-1]*-1, dp[i]+t[i-1]*i-sum[i-1], i});
    }
    st.add({t[n-1]*-1, t[n-1]*n-sum[n-1], n});
}
ll dis[maxn];

int main() {
    ios::sync_with_stdio(0);
    ll n,m,p;
    cin >> n >> m >> p;
    for (int i=1; i<n; i++) cin>>dis[i];
    for (int i=1; i<n; i++) dis[i] += dis[i-1];

    for (int i=0; i<m; i++) {
        ll h, s; cin>>h>>s;
        t[i] = s - dis[--h];
    }
    sort(t, t+m);

    sum[0] = t[0];
    for (int i=1; i<m; i++) sum[i] = t[i] + sum[i-1];

    st.add({t[m-1]*-1, t[m-1]*m-sum[m-1], m});
    for (int i=0; i<p-1; i++) {
        calc_dp(m);
        add_st(m);
    }
    ll ans = st.getmin(0,0);
    cout << ans << '\n';
}
