#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const long long mod = 1e9+7;

ll exp(ll a, ll x){
    ll ans = 1;
    while(x){
        if(x%2) ans = (ans*a)%mod;
        a = (a*a)%mod;
        x/=2;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N,M;
    cin>>N>>M;
    vll vl(N);
    for(int i=0; i<N; i++) cin>>vl[i];

    vll facts(N+1);
    facts[0] = 1;
    for(int i=1; i<N+1; i++) facts[i] = (facts[i-1]*i)%mod;

    ll Q = facts[N];
    Q = exp(Q,mod-2);

    map<ll,ll> mp;
    for(int i=0; i<N; i++) mp[vl[i]]++;
    for(auto& x : mp){
        Q = (Q * facts[x.second])%mod;
    }
    cout << Q << '\n';

    for(int i=0; i<M; i++){
        ll idx, x; cin>>idx>>x;
        idx--;
        ll y = vl[idx];
        vl[idx] = x;

        ll p1 = facts[mp[y]];
        ll p2 = facts[mp[x]];
        mp[y]--;
        mp[x]++;
        Q = (Q*facts[mp[y]])%mod;
        Q = (Q*facts[mp[x]])%mod;
        Q = (Q*exp(p1,mod-2))%mod;
        Q = (Q*exp(p2, mod-2))%mod;
        cout << Q << '\n';
    }
}
