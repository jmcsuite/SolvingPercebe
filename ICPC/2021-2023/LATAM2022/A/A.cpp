#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn = 1001;

void DFS(ll x, vll vadj[maxn], ll vis[maxn]){
    if(vis[x]) return;
    vis[x] = 1;
    for(ll y : vadj[x]){
        DFS(y, vadj, vis);
    }
}

vll normal[maxn];
vll rev[maxn];

ll visRev[maxn];
ll vis1[maxn];
ll vis2[maxn];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    auto clear = [&](){
        for(int i=0; i<N; i++){
            visRev[i]=0;
            vis1[i]=0;
            vis2[i]=0;
        }
    };

    for(int i=0; i<N; i++){
        ll a,b; cin>>a>>b; a--; b--;
        normal[i].push_back(a);
        normal[i].push_back(b);
        rev[a].push_back(i);
        rev[b].push_back(i);
    }

    for(int i=0; i<N; i++){
        clear();
        DFS(i,rev,visRev);
        ll a,b;
        a=normal[i][0]; b=normal[i][1];
        vis1[i]=1;
        vis2[i]=1;
        DFS(a,rev,vis1);
        DFS(b,rev,vis2);
        bool se=false;
        for(int j=0; j<N; j++){
            if(j==i) continue;
            if(vis1[j] && vis2[j] && visRev[j]) {
                se=true;
                break;
            }
        }
        if(se) cout << "Y";
        else cout << "N";
    }
    cout << '\n';
}
