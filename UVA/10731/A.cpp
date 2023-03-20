#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=27;

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
        for(int y: vadj[x]){
            if(inStack[y]){
                lo[x] = min(lo[x], hi[y]);
                continue;
            }
            lo[x] = min(lo[x], tarjan(y, vadj));
        }

        if(lo[x] == hi[x]){
            int currSz = 0;
            vll thisComp;
            while(st.top() != x){
                thisComp.push_back(st.top());
                inStack[st.top()] = 0;
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
            inStack[st.top()] = 0;
            myComp[st.top()]=scc;
            int y=st.top();
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

    void tarjanMain(int N, vector<vll>& vadj){
        clear(N);
        for(int i=0; i<N; i++){
            if(vis[i] == 0) tarjan(i,vadj);
        }
    }
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    bool se = false;
    while(1){
        ll N; cin>>N;
        if(N==0) break;
        if(se){
            cout << '\n';
        }
        se = true;
        map<ll,ll> mp;
        vector<vll> vadj(maxn);
        for(int i=0; i<N; i++){
            vector<char> inp(6);
            for(int j=0; j<6; j++) cin>>inp[j];
            for(int j=0; j<6; j++) inp[j]-='A';
            for(int j=0; j<6; j++) mp[inp[j]] = 1;
            for(int j=0; j<5; j++) {
                if(inp[j] == inp[5]) continue;
                vadj[inp[5]].push_back(inp[j]);
            }
        }
        Tarjan::tarjanMain(maxn,vadj);
        vector<vll> myComp;
        for(int i=0; i<Tarjan::scc; i++){
            if(Tarjan::comps[i].size() == 1 && mp[Tarjan::comps[i][0]] == 0) continue;
            if(Tarjan::comps[i].size() == 0) continue;
            myComp.push_back(Tarjan::comps[i]);
        }
        int M=myComp.size();
        for(int i=0; i<M; i++) sort(myComp[i].begin(), myComp[i].end());
        sort(myComp.begin(), myComp.end(), [&](vll& a, vll& b){
                return a[0] < b[0];
                });
        
        // print answer
        for(int i=0; i<M; i++){
            for(size_t j=0; j<myComp[i].size(); j++){
                cout << char(myComp[i][j]+'A') << (j+1 == myComp[i].size() ? '\n' : ' ');
            }
        }
    }
}
    



