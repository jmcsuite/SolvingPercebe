#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=1000;
ll pa[maxn];
ll pb[maxn];
ll dp[maxn][maxn];
vll vadjA[maxn];
vll vadjB[maxn];
ll level[maxn];
vll levelAdj[maxn];
ll np[maxn];

void clear(ll N){
    for(int i=0; i<N; i++){
        pa[i]=-1;
        pb[i]=-1;
        vadjA[i].clear();
        vadjB[i].clear();
        level[i]=-1;
        np[i]=-1;
        levelAdj[i].clear();
        for(int j=0; j<N; j++) dp[i][j]=-1;
    }
}

bool func(ll x, ll p){
    if(dp[x][p] != -1) return dp[x][p];
    if(pb[x] == p) return 1;
    if(pb[x] != -1) return 0;
    bool ans=0;
    for(ll z: vadjB[p]){
        bool se=1;
        if(z < x) continue;
        for(ll y: vadjA[x]) se &= func(y,z);
        if(se) ans=1;
    }
    dp[x][p]=ans;
    return ans;
}

void build(ll x, ll d){
    levelAdj[d].push_back(x);
    for(ll y: vadjA[x]) build(y,d+1);
}

int main(){
    ll T; cin>>T;
    while(T--){
        ll N; cin>>N; clear(N);
        for(int i=1; i<N; i++){
            ll c, p; cin>>c>>p;
            c--; p--;
            pa[c]=p;
            vadjA[p].push_back(c);
        }
        ll M; cin>>M;
        unordered_map<ll,ll> alive;
        for(int i=1; i<M; i++){
            ll c, p; cin>>c>>p;
            c--; p--;
            pb[c] = p;
            vadjB[p].push_back(c);
            alive[c]=1;
            alive[p]=1;
        }
        ll root=-1;
        for(int i=0; i<N; i++) if(pa[i] == -1) root=i;

        build(root,0);
        cout << N-M << '\n';
        for(ll y: levelAdj[1]){
            np[y]=root;
        }
        for(int i=0; i<N; i++){
            if(pb[i] == -1) np[i]=pa[i];
            else np[i]=pb[i];
        }
        for(int i=0; i<N; i++){
            for(ll y: levelAdj[i]){
                if(alive[y]) continue;
                for(ll z: levelAdj[i]){
                    if(!alive[z]) continue;
                    if(z < y) continue;
                    if(np[z] != np[y]) continue;
                    bool se=1;
                    for(ll k: vadjA[y]){
                        se &= func(k,z);
                    }
                    if(se){
                        for(ll k: vadjA[y]) np[k] = z;
                        cout << y+1 << ' ' << z+1 << '\n';
                        break;
                    }
                }
            }
        }
    }
}
            


