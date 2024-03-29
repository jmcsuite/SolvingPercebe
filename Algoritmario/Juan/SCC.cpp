const int maxn = // add maxn

namespace Tarjan{
    int scc=0; // Number of resulting scc;
    bool inStack[maxn];
    int lo[maxn];
    int hi[maxn];
    int vis[maxn];
    stack<int> st;
    int step=0;
    int sz[maxn]; //Size of each component. Components are 0 indexed
    vector<vll> comps; // Each component
    int myComp[maxn]; // Maps each node to each component
    unordered_set<ll> compVadj[maxn]; // New graph. Components are 0 indexed

    void clear(int N){
        scc=0;
        step = 0;
        for(int i=0; i<N; i++){
            vis[i] =0;
            inStack[i] =0;
            sz[i] = 0;
            myComp[i] =0;
            compVadj[i].clear();
        }
        comps.clear();
    }

    int tarjan(int x, vector<vll>& vadj){
        if(vis[x]) return maxn+2;
        vis[x] = 1;
        inStack[x] = 1;
        st.push(x);
        lo[x] = hi[x] = step++;
        for(int y : vadj[x]){
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

    void tarjanMain(int N, vector<vll>& vadj){ // Use this. 
        clear(N); // Modify this if you use a range [1,N]
        for(int i=0; i<N; i++){  //Modify this if your nodes start from 1
            if(vis[i] == 0) tarjan(i,vadj);
        }
    }
}
