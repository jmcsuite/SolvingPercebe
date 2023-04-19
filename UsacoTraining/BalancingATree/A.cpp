#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn=100000;

ll pi[maxn];
vll vadj[maxn];
ll L[maxn];
ll R[maxn];
ll val[maxn];

void func(ll x, ll p, ll mini, ll maxi){
    ll myV = mini;
    if(L[x] >= mini) myV = L[x];
    if(R[x] <= mini) myV = R[x];
    val[x] = myV;
    mini = min(mini, val[x]);
    maxi = max(maxi, val[x]);
    for(ll y: vadj[x]){
        if(y == p) continue;
        func(y,x, mini, maxi);
    }
}

pll dp(ll x, ll p, ll d){
    ll mini = -1000000000;
    ll maxi = 2000000000;
    for(ll y: vadj[x]){
        if(y == p) continue;
        pll r = dp(y,x,d);
        if(r.first > r.second) return r;
        mini = max(r.first,mini);
        maxi = min(maxi,r.second);
    }
    pll tmp(mini, maxi);
    pll a1 = tmp;
    a1.first = max(a1.first, L[x]);
    a1.second = min(a1.second, R[x]);
    if(a1.first > a1.second) return a1;
    tmp.first = max(tmp.first, L[x]-d);
    tmp.second = min(tmp.second, R[x]+d);
    return tmp;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T,B;
    cin>>T>>B;
    while(T--){
        ll N; cin>>N;
        for(int i=0; i<N; i++) vadj[i].clear();
        for(int i=1; i<N; i++){
            ll a; cin>>a; a--;
            vadj[i].push_back(a);
            vadj[a].push_back(i);
        }
        for(int i=0; i<N; i++) cin>>L[i]>>R[i];
        ll prevAns=L[0];

        auto check = [&](ll d){
            pll pp = dp(0,0,d);
            ll x = pp.first;
            ll y = pp.second;
            if(x > y) return false;
            x = max(x,L[0]);
            prevAns=x;
            return true;
        };

        ll inc = 1000000001;
        ll ans = inc;
        while(inc != 0){
            if(ans-inc >= 0 && check(ans-inc)) ans-=inc;
            else inc/=2;
        }
        cout << ans << '\n';
        if(B == 0) continue;
        func(0,0,prevAns, prevAns);
        for(int i=0; i<N; i++) cout << val[i] << (i == N-1 ? '\n' : ' ');
    }
}
