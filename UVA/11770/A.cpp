#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;
const int maxn=10004;

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

    int tarjan(int x, vector<vll>& vadj){
        if(vis[x]) return maxn+2;
        vis[x]=1;
        inStack[x]=1;
        st.push(x);
        lo[x]=hi[x]=step++;
        for(int y:vadj[x]){
            if(inStack[y]){
                lo[x]=min(lo[x],hi[y]);
                continue;
            }
            lo[x]=min(lo[x], tarjan(y,vadj));
        }
        if(lo[x] == hi[x]){
            int currSz=0;
            vll thisComp;
            while(st.top() != x){
                thisComp.push_back(st.top());
                inStack[st.top()]=0;
                myComp[st.top()] = scc;
                int y = st.top();
                for(int z: vadj[y]){
                    if(inStack[z]) continue;
                    z = myComp[z];
                    if(z == scc) continue;
                    compVadj[scc].insert(z);
                }
                currSz++;
                st.pop();
            }
            thisComp.push_back(x);
            inStack[st.top()]=0;
            myComp[st.top()]=scc;
            int y=st.top();
            for(int z : vadj[y]){
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

    void tarjanMain(int N, vector<vll>& vadj){ 
        clear(N);
        for(int i=0; i<N; i++){
            if(vis[i] == 0) tarjan(i,vadj);
        }
    }
}

int main(){
    ll Q,T;
    Q=0; cin>>T;
    while(T--){
        ll N,M;
        cin>>N>>M;
        vector<vll> vadj(N);
        for(int i=0; i<M; i++){
            ll a,b; cin>>a>>b; 
            a--; b--;
            vadj[a].push_back(b);
        }
        Tarjan::tarjanMain(N,vadj);
        map<ll,ll> cc;
        for(int i=0; i<Tarjan::scc; i++){
            for(int y: Tarjan::compVadj[i]){
                cc[y]++;
            }
        }

        ll ans=0;
        for(int i=0; i<Tarjan::scc; i++){
            if(cc[i] == 0) ans++;
        }
        cout << "Case " << ++Q << ": " << ans << '\n';
    }
}
