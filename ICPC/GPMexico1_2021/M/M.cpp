#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

map<ll,ll> exists;
const int maxn=361;
const int mod = 360;
int inp[maxn];
int vis[maxn];
int DFS(ll x, ll dx){
    x%=mod;
    x+=mod;
    x%=mod;
    if(exists[x] == 0) return 0;
    if(vis[x]) return 0;
    vis[x] = 1;
    return 1+DFS(x+dx,dx);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    for(int i=0; i<N; i++) cin>>inp[i];
    for(int i=0; i<N; i++) exists[inp[i]]=1;
    ll ans = 0;
    for(int i=1; i<360; i++){
        for(int j=0; j<maxn;j++) vis[j] =0;
        ll n1 = 0;
        for(int j=0; j<N; j++){
            ll n2 = 0;
            n2 += DFS(inp[j],i);
            n2 += DFS(inp[j]-i,-1*i);
            n2 /= 2;
            n1+=n2;
        }
        ans = max(ans, n1);
    }
    cout << ans << '\n';
}

    
