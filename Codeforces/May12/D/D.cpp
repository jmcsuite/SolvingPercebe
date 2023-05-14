#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;
 
 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,Q;
    cin>>N>>Q;
    vll vl(N);
    for(int i=0; i<N; i++) cin>>vl[i];
    sort(vl.begin(),vl.end());
    auto func=[&](ll n, ll target, ll k){
        ll rest=(k-n)/2;
        for(int i=0; i<N; i++){
            ll add=max(ll(0),k-i);
            if(i >= n) add=0;
            if(vl[i]+add< target) return false;
            ll diff=vl[i]+add-target;
            rest-=diff;
        }
        if(rest > 0) return false;
        return true;
    };
 
    while(Q--){
        ll q; cin>>q;
        if(N==1){
            if(q%2==0){
                cout <<vl[0]-q/2 << (Q == 0 ? '\n' : ' ');
                continue;
            }else{
                cout << vl[0]-((q-1)/2)+q << (Q == 0 ? '\n' : ' ');
                continue;
            }
        }
 
        ll n=N;
        if(N%2 != q%2) n--;
        ll ans=0;
        ll inc=10000000000;
        while(inc != 0){
            if(func(n,ans+inc,q)) ans+=inc;
            else inc/=2;
        }
        if(n!=N) ans=min(ans,vl[N-1]);
        cout << ans << (Q == 0 ? '\n' : ' ');
    }
}
 
