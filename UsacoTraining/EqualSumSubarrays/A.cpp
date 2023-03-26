#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn=500;
using item = pair<ll,pll>;
ll vl[maxn];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    for(int i=0; i<N; i++) cin>>vl[i];
    for(int i=1; i<N; i++) vl[i]+=vl[i-1];
    set<item> st;
    vector<item> vs;
    for(int i=0; i<N; i++){
        for(int j=i+1; j<=N; j++){ // [i,j)
            ll val = vl[j-1];
            if(i > 0) val-=vl[i-1];
            vs.push_back({val,{i,j}});
        }
    }
    sort(vs.begin(),vs.end());

    for(int i=0; i<N; i++){
        ll ans=1e17;
        ll prevIn=ans*-1;
        ll prevOut=ans*-1;
        for(item& x: vs){
            if(x.second.first<=i && x.second.second>i){
                prevIn=x.first;
                ans = min(ans,prevIn-prevOut);
            }else{
                prevOut=x.first;
                ans = min(ans,prevOut-prevIn);
            }
        }
        cout << ans << '\n';
    }
}
            
