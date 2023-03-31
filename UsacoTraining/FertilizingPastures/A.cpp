#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=2e5;
ll depth[maxn];
ll nodes[maxn];
ll sum[maxn];
ll ai[maxn];
vll adj[maxn];
vll goodAdj[maxn];

void calc(ll x, ll p, vll vadj[maxn]){
    for(ll y: vadj[x]){
        if(y == p) continue;
        goodAdj[x].push_back(y);
        calc(y,x,vadj);
        sum[x]+=sum[y];
        nodes[x]+=nodes[y];
        depth[x]=max(depth[x],depth[y]);
    }
    depth[x]++;
    nodes[x]++;
    sum[x]+=ai[x];
}

ll dp[maxn];

void dp0(ll x, vll vadj[maxn]){
    sort(vadj[x].begin(), vadj[x].end(), [&](ll a, ll b){
            return sum[a]*nodes[b] >= sum[b]*nodes[a];
            });
    ll carry=1;
    ll ans=0;
    for(size_t j=0; j<vadj[x].size(); j++){
        dp0(vadj[x][j],vadj);
        ans+=dp[vadj[x][j]];
        ans+=carry*sum[vadj[x][j]];
        carry+=nodes[vadj[x][j]]*2;
    }
    //cout << "DP0 " << x << ' ' << ans << endl;
    dp[x]=ans;
}

ll dpHard[maxn];
void solve(ll x, vll vadj[maxn]){
    if(vadj[x].size() == 0){
        dpHard[x]=dp[x];
        return;
    }
    for(size_t j=0; j<vadj[x].size(); j++){
        solve(vadj[x][j],vadj);
    }
    sort(vadj[x].begin(), vadj[x].end(), [&](ll a, ll b){
            return sum[a]*nodes[b] >= sum[b]*nodes[a];
            });
   
    ll tot=dp[x];
    ll ans=LONG_LONG_MAX;
    ll sumAcum=0;
    ll target=depth[x]-1;
    ll nodesAcum=0;
    for(ll j=vadj[x].size()-1; j>=0; j--){
        ll y = vadj[x][j];
        if(depth[y] == target){
            ll step = tot-dp[y]+dpHard[y]-2*nodes[y]*sumAcum+2*nodesAcum*sum[y];
            ans=min(ans,step);
        }
        sumAcum+=sum[y];
        nodesAcum+=nodes[y];
    }
    dpHard[x]=ans;
    return;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,T;
    cin>>N>>T;
    for(int i=1; i<N; i++){
        ll a,c; cin>>a>>c;
        a--;
        adj[a].push_back(i);
        adj[i].push_back(a);
        ai[i]=c;
    }

    calc(0,0,adj);
    dp0(0,goodAdj);
    solve(0,goodAdj);
    ll ans=dp[0];
    if(T == 1) ans = dpHard[0];
    
    ll f=(N-1)*2;
    if(T==1) f = f+1-depth[0];
    cout << f << ' ' << ans << '\n';
}
