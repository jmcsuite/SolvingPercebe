#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Slope{
    ll m, x;
    Slope(ll a, ll b) : m(a), x(b) {}
};

deque<Slope> dq;

void Add(Slope x) {
    while (dq.size() >= 2) {
        Slope a = dq[dq.size()-2];
        Slope b = dq[dq.size()-1];
        if (double(x.x - a.x)/double(a.m-x.m) > double(b.x-a.x)/double(a.m-b.m)) break;
        dq.pop_back();
    }
    dq.push_back(x);
}

ll Eval(ll i, ll x) {
    return dq[i].m*x + dq[i].x;
}
ll Query(ll x) {
    while (dq.size() >= 2) {
        if (Eval(0,x) > Eval(1,x)) break;
        dq.pop_front();
    }
    return Eval(0,x);
}


const int maxn=1e5;
ll dp[maxn];
ll vl[maxn];
ll p[maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    for (int i=0; i<N; i++) cin >> vl[i];
    for (int i=0; i<N; i++) cin >> p[i];
    dp[N-1] = 0;
    Add({(vl[N-1]-1)*-1,0});
    for (int i=N-2; i>=0; i--) {
        dp[i]=p[i];
        dp[i]-=Query(p[i]);
        Add({(vl[i]-1)*-1, dp[i]*-1});
    }
    cout << dp[0] << '\n';
}
