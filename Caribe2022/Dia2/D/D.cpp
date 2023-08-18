#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=400001;

namespace aho{
    vector<string> vs;
    ll val[maxn+1];
    ll smatch[maxn+1];

    ll p[maxn+1];
    ll pchar[maxn+1];
    map<ll,ll> vadj[maxn+1];
    ll nCount=1;
    const long long root=0;

    ll flink[maxn+1];
    ll olink[maxn+1];

    namespace lca{
        const int maxPow=21;
        ll f1[maxn];
        ll depth[2*maxn];
        ll depthAns[2*maxn];
        ll cc=0;
        ll dpVal[2*maxn][maxPow];
        ll dpAns[2*maxn][maxPow];

        void build(int x, int p, int d, map<ll,ll> vadj[maxn+1]){
            f1[x]=cc;
            depth[cc]=d;
            depthAns[cc]=x;
            cc++;
            for(pll yy: vadj[x]){
                ll y = yy.second;
                if(y==p) continue;
                build(y,x,d+1,vadj);
                depth[cc]=d;
                depthAns[cc]=x;
                cc++;
            }
        }

        void buildPow(ll N){
            for(int i=0; i<(2*N-1); i++){
                dpAns[i][0]=depthAns[i];
                dpVal[i][0]=depth[i];
            }
            for(int j=1; j<maxPow; j++){
                for(int i=0; i<(2*N-1); i++){
                    dpAns[i][j]=dpAns[i][j-1];
                    dpVal[i][j]=dpVal[i][j-1];
                    int nex = i+(1<<(j-1));
                    if(nex >= 2*N-1) continue;
                    if(dpVal[nex][j-1] < dpVal[i][j]){
                        dpVal[i][j] = dpVal[nex][j-1];
                        dpAns[i][j]=dpAns[nex][j-1];
                    }
                }
j           }
        }

        ll getLca(ll a, ll b){
            ll pa = f1[a];
            ll pb = f1[b];
            ll fa = min(pa, pb); ll fb = max(pa,pb);
            ll dis = fb-fa+1;
            ll pp = 63-__builtin_clzll(dis);
            ll nex = fb-(1<<pp)+1;
            ll ans = dpAns[fa][pp];

            if(dpVal[nex][pp] < dpVal[fa][pp]) return dpAns[nex][pp];
            return ans;
        }

        void real_build(ll x, ll N, map<ll,ll> vadj[maxn+1]){
            cc=0;
            build(x,x,0,vadj);
            buildPow(N);
        }
    }



    ll addString(ll i, char c){
        if(vadj[i].find(c) != vadj[i].end()) return vadj[i][c];
        ll node = nCount++;
        p[node]=i;
        pchar[node]=c;
        vadj[i][c]=node;
        return node;
    }

    void build(){
        pchar[root]=-1;
        for(int i=0; i<maxn; i++) smatch[i]=-1;

        lca::real_build(root,nCount,vadj);

        queue<ll> q; q.push(root);
        while(!q.empty()){
            ll x=q.front(); q.pop();
            for(pll yy: vadj[x]) q.push(yy.second);
            ll nx = flink[p[x]];
            ll c = pchar[x];
            while(nx != root && (vadj[nx].find(c) == vadj[nx].end()
                        || lca::getLca(vadj[nx][c], x) != vadj[nx][c])) nx=flink[nx];

            if((vadj[nx].find(c) == vadj[nx].end() || lca::getLca(vadj[nx][c], x) != vadj[nx][c]) || vadj[nx][c] == x) flink[x]=root;
            else flink[x]=vadj[nx][c];

            if(smatch[flink[x]] != -1) olink[x] = flink[x];
            else olink[x] = olink[flink[x]];
        }
    }

    ll ans=0;
    void match(ll node, ll pos){
        ans++;
    }

    void aho(string& T, ll id){
        ll x=root;
        for(int c=0; c<(ll)T.size(); c++){
            while(x != root && 
                    (vadj[x].find(T[c]) == vadj[x].end() || lca::getLca(vadj[x][T[c]], id) != vadj[x][T[c]])) x = flink[x];
            if(vadj[x].find(T[c]) == vadj[x].end() || 
                    lca::getLca(vadj[x][T[c]], id) != vadj[x][T[c]]) continue;
            x = vadj[x][T[c]];
            if(x == id) match(x,c);
            ll mx = olink[x];
            while(mx != root){
                match(mx,c);
                mx = olink[mx];
            }
        }
    }
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M;
    cin>>N;
    vll nodes;
    for(int i=0; i<N; i++){
        ll q; cin>>q;
        if(q==1){
            char b; cin>>b;
            ll l = aho::addString(aho::root,b);
            nodes.push_back(l);
        }else{
            ll a; char b; cin>>a>>b;
            a--;
            ll l = aho::addString(nodes[a],b);
            nodes.push_back(l);
        }
    }

    aho::build();
    cin>>M;
    for(int i=0; i<M; i++){
        ll a; string b;
        cin>>a>>b;
        a--;
        ll l = nodes[a];
        aho::aho(b,l);
        cout << aho::ans << '\n';
        aho::ans=0;
    }
}

            



