#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=2e5+4;

namespace Tarjan{
    int scc=0;
    bool inStack[maxn];
    int lo[maxn];
    int hi[maxn];
    int vis[maxn];
    stack<int> st;
    int step=0;
    int sz[maxn];
    vector<vll> comps;
    int myComp[maxn];
    unordered_set<ll> compVadj[maxn];
    int visEdge[maxn];

    void clear(int N){
        scc=0;
        step=0;
        for(int i=0; i<N; i++){
            vis[i]=0;
            inStack[i]=0;
            sz[i]=0;
            myComp[i]=0;
            compVadj[i].clear();
        }
        comps.clear();
    }

    int tarjan(int x, vector<vll>& vadj, multiset<pll>& ed){
        if(vis[x]) return maxn+2;
        vis[x] = 1;
        inStack[x]=1;
        st.push(x);
        lo[x]=hi[x]=step++;
        for(int y : vadj[x]){
            if(ed.find({y,x}) == ed.end() && ed.find({x,y}) == ed.end()) continue;
            auto i1 = ed.find({y,x});
            auto i2 = ed.find({x,y});
            if(i1 != ed.end()) ed.erase(i1);
            else ed.erase(i2);
            
            if(inStack[y]){
                lo[x] = min(lo[x], hi[y]);
                continue;
            }
            lo[x] = min(lo[x], tarjan(y, vadj, ed));
        }

        if(lo[x] == hi[x]){
            int currSz=0;
            vll thisComp;
            while(st.top() != x){
                thisComp.push_back(st.top());
                inStack[st.top()] = 0;
                myComp[st.top()] = scc;
                int y = st.top();
                for(int z : vadj[y]){
                    if(inStack[z]) continue;
                    z = myComp[z];
                    if(z == scc) continue;
                    compVadj[scc].insert(z);
                }
                currSz++;
                st.pop();
            }
            thisComp.push_back(x);
            inStack[st.top()] = 0;
            myComp[st.top()] = scc;
            int y = st.top();
            for(int z: vadj[y]){
                if(inStack[z]) continue;
                z = myComp[z];
                if(z == scc) continue;
                compVadj[scc].insert(z);
            }
            st.pop();
            currSz++;
            comps.push_back(thisComp);
            sz[scc] = currSz;
            scc++;
        }
        return lo[x];
    }

    void tarjanMain(int N,vector<vll>& vadj, multiset<pll>& edges){
        clear(N);
        for(int i=0; i<N; i++){
            if(vis[i] == 0) tarjan(i,vadj, edges);
        }
    }
}
map<pll,ll> lca;
int marked[maxn];
int fd[maxn];
vll qLCA[maxn];

ll find(ll x){
    if(x == fd[x]) return fd[x];
    return fd[x] = find(fd[x]);
}

void uni(ll a, ll b){ // a becomes parent of b;
    ll fa = find(a);
    ll fb = find(b);
    fd[fb] = fa;
}

void DFS(ll x, ll p,unordered_set<ll> vadj[maxn]){
    if(marked[x]) return;
    marked[x] = 1;
    fd[x] = x;
    for(ll y: qLCA[x]){
        if(marked[y]){
            ll aa = min(x,y);
            ll bb = max(x,y);
            lca[pll(aa,bb)]=find(y);
        }
    }
    //cout << "IN DFS: " << x << endl;
    for(ll y: vadj[x]){
        if(y == p) continue;
        DFS(y, x, vadj);
        uni(x,y);
    }
    //cout << "OUT DFS: " << x << endl;
}

ll sending[maxn];
ll rec[maxn];

void Solve(ll x,ll p, unordered_set<ll> vadj[maxn]){
    if(marked[x]) return;
    marked[x]=1;
    for(ll y: vadj[x]){
        if(y == p) continue;
        Solve(y,x,vadj);
        sending[x]+=sending[y];
        rec[x]+=rec[y];
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M,Q; cin>>N>>M>>Q;
    multiset<pll> st;
    vector<vll> vadj(N);
    vpll queries(Q);
    vpll dirs(Q);
    for(int i=0; i<M; i++){
        ll a,b; cin>>a>>b;
        a--; b--;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
        st.insert({a,b});
    }
    Tarjan::tarjanMain(N,vadj,st);
    ll superNode = Tarjan::scc;
    //cout << "Number of scc: " << Tarjan::scc << endl;
    for(int i=0; i<Tarjan::scc; i++){
        Tarjan::compVadj[superNode].insert(i);
    }
    for(int i=0; i<Q; i++){
        ll a,b; cin>>a>>b;
        a--; b--;
        a = Tarjan::myComp[a];
        b = Tarjan::myComp[b];
        if(a == b){
            queries[i].first = -1;
        }
        if(a == b) continue;
        queries[i].first = min(a,b);
        queries[i].second = max(a,b); 
        dirs[i].first = a;
        dirs[i].second = b;
        //cout << "Query: " << i << ' ' << a << ' ' << b << endl;
        qLCA[a].push_back(b);
        qLCA[b].push_back(a);
    }
    
    for(int i=0; i<Tarjan::scc; i++){
        for(ll y: Tarjan::compVadj[i]){
            //cout << "Duplicating " << i << ' ' << y << endl;
            Tarjan::compVadj[y].insert(i);
        }
    }
    //cout << "Checand Componentes" << endl;
    //for(int i=0; i<Tarjan::scc; i++){
        //for(ll y: Tarjan::comps[i]){
            //cout << y << ' ';
        //}
        //cout << endl;
    //}
    //cout << "FIN Checand Componentes" << endl;
    DFS(superNode, superNode, Tarjan::compVadj);
    for(int i=0; i<Q; i++){
        if(queries[i].first == -1) continue;
        ll lc = lca[queries[i]];
        //cout << "Answer: " << i << ' ' << lc << endl;
        if(lc == Tarjan::scc){
            cout << "No\n";
            return 0;
        }
        sending[lc]--;
        rec[lc]--;
        sending[dirs[i].first]++;
        rec[dirs[i].second]++;
    }

    for(int i=0; i<= Tarjan::scc; i++) marked[i] = 0;
    Solve(superNode,superNode, Tarjan::compVadj);
    for(int i=0; i< Tarjan::scc; i++){
        if(sending[i] && rec[i]){
            cout << "No\n";
            //cout << "Here Not " << i << ' ' << sending[i] << ' ' << rec[i] << endl;
            return 0;
        }
    }
    cout << "Yes\n";
}
