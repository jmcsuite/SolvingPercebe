#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

struct Slope{ 
    ll m, x;
    Slope(ll a, ll b) : m(a), x(b) {}
};

double intersect(Slope a, Slope b) {
    return double(b.x-a.x) / double(a.m-b.m);
}

deque<Slope> dq;
void add(Slope x) {
    while (dq.size() >= 2) {
        Slope a = dq[0];
        Slope b = dq[1];
        if (intersect(x,b) < intersect(a,b)) break;
        dq.pop_front();
    }
    dq.push_front(x);
}

ll eval(ll t, ll i) {
    return dq[i].m * t + dq[i].x;
}

ll getMax(ll t) {
    while (dq.size() >= 2) {
        if (eval(t, dq.size()-1) > eval(t, dq.size()-2)) break;
        dq.pop_back();
    }
    return eval(t, dq.size()-1);
}

const int maxn = 1e6;
ll dp[maxn];
ll s[maxn];
ll vl[maxn];

ll p(ll x) {
    if (x == 0) return 0;
    return s[x-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    ll a,b,c; cin >> a >> b >> c;
    for (int i=0; i<N; i++) cin>>vl[i];
    s[0] = vl[0];
    for (int i=1; i<N; i++) s[i]=s[i-1]+vl[i];
    dp[N-1] = vl[N-1]*vl[N-1]*a + b*vl[N-1] + c;
    if (N == 1) {
        cout << dp[0] << '\n';
        return 0;
    }

    add({-a*2*s[N-2], dp[N-1]+a*s[N-2]*s[N-2]+b*s[N-2]});

    for (int i=N-2; i>=0; i--) {
        dp[i] = getMax(p(i)); 
        dp[i] += a*p(i)*p(i)+c-b*p(i);

        ll all = a*(s[N-1]-p(i))*(s[N-1]-p(i))+b*(s[N-1]-p(i))+c;
        dp[i] = max(dp[i], all);
        if (i == 0) break;
        add({-a*2*s[i-1], dp[i]+a*s[i-1]*s[i-1]+b*s[i-1]});
    }
    cout << dp[0] << '\n';
}
