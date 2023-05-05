#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

ll DFS(ll x, ll p, ll t,vector<vll>& vadj, vll& nums){
    if(x == t) return nums[x];
    for(ll y: vadj[x]){
        if(y == p) continue;
        ll nans=DFS(y,x,t,vadj,nums);
        if(nans != 0) return nums[x]*nans;
    }
    return 0;
}
    


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N; cin>>N;
        vector<vll> vadj(N);
        for(int i=0; i<N-1; i++){
            ll a,b; cin>>a>>b;
            a--;
            b--;
            vadj[a].push_back(b);
            vadj[b].push_back(a);
        }
        vll nums(N);
        for(int i=0; i<N; i++) cin>>nums[i];
        ll Q; cin>>Q;
        while(Q--){
            ll a,b; cin>>a>>b;
            a--; b--;
            ll ans=DFS(a,a,b, vadj, nums);
            ll cans=0;
            for(int i=1; i<=ans; i++){
                if(ans%i==0) cans++;
            }
            cout << cans << '\n';
        }
    }
}


