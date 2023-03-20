#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll= vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=101;

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
            vis[i] = 0;
            inStack[i]=0;
            sz[i]=0;
            myComp[i]=0;
            compVadj[i].clear();
        }
        comps.clear();
    }

    int tarjan(int x,vector<vll>& vadj){
        //cout << "TARJAN IN: " << x << endl;
        if(vis[x]) return maxn+2;
        vis[x]=1;
        inStack[x]=1;
        st.push(x);
        lo[x]=hi[x]=step++;
        for(int y: vadj[x]){
            if(inStack[y]){
                lo[x] = min(lo[x], hi[y]);
                continue;
            }
            lo[x] = min(lo[x], tarjan(y, vadj));
        }
        //cout << "LOWS " << x+1 << ' ' << lo[x] << ' ' << hi[x] << endl;

        if(lo[x] == hi[x]){
            int currSz=0;
            vll thisComp;
            while(st.top() != x){
                thisComp.push_back(st.top());
                inStack[st.top()]=0;
                myComp[st.top()]=scc;
                int y=st.top();
                for(int z: vadj[y]){
                    if(inStack[z]) continue;
                    z=myComp[z];
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
            for(int z:vadj[y]){
                if(inStack[z]) continue;
                z=myComp[z];
                if(z==scc) continue;
                compVadj[scc].insert(z);
            }
            st.pop();
            currSz++;
            comps.push_back(thisComp);
            sz[scc]=currSz;
            scc++;
        }
        return lo[x];
    }

    void tarjanMain(int N, vector<vll>& vadj){
        clear(N);
        for(int i=0; i<N; i++){
            //cout << "VIS CHECK: " << N << ' ' << i << ' ' << vis[i] << endl;
            if(vis[i] == 0) tarjan(i, vadj);
        }
    }
}

map<string,ll> mp;
map<ll,string> rev;
int aaCounter=0;
ll getNum(string& a){
    if(mp[a] == 0){
        mp[a] = ++aaCounter;
        rev[aaCounter]=a;
    }
    //cout << "GETNUM: " << a << ' ' << mp[a] << endl;
    return mp[a];
}
ll ansSz = 1000000;
ll ansComp = 0;
void DFS(ll x, unordered_set<ll> vadj[maxn], vll& vis, vll& aans){
    if(vis[x]) return;
    vis[x]=1;
    aans.push_back(x);
    for(ll y: vadj[x]){
        DFS(y,vadj,vis, aans);
    }
    return;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N;
    while(cin>>N){
        if(N == 0) return 0;
        aaCounter=0;
        mp.clear();
        rev.clear();
        ansComp=0;
        ansSz=1000000;


        string dummy;
        getline(cin,dummy);
        vector<vll> vadj(N+1);
        for(int i=0; i<N; i++){
            string line;
            getline(cin,line);
            stringstream ss(line);
            vector<string> vs;
            string aa;
            while(ss>>aa){
                vs.push_back(aa);
                //cout << i << " " << aa << endl;
            }
            int s=getNum(vs[0]);
            //cout << s << endl;
            for(size_t j=1; j<vs.size(); j++){
                int t = getNum(vs[j]);
                vadj[s-1].push_back(t-1);
                //cout << vs[0] << ' ' << s << ' ' << vs[j] << ' ' << t << endl;
            }
            //cout << s << endl;
        }
        Tarjan::tarjanMain(N,vadj);
        vll vis(Tarjan::scc);
        vector<string> out;
        //cout << "SCC " << Tarjan::scc << endl;
        for(int i=0; i<Tarjan::scc; i++){
            if(Tarjan::sz[i] == 1) continue;
            vll aans;
            DFS(i,Tarjan::compVadj, vis, aans);
            for(int ii: aans){
                for(int y: Tarjan::comps[ii]){
                    out.push_back(rev[y+1]);
                }
            }
        }
        sort(out.begin(), out.end());
        cout << out.size() << '\n';
        for(size_t i=0; i<out.size(); i++){
            cout << out[i] << (i == out.size()-1 ? '\n' : ' ');
        }

    }
}
