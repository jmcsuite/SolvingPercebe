#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

ll N,M, T;
const int maxn = 30;
unordered_set<ll> vadj[maxn];
map<string,ll> mp;
map<ll, string> rev;
int nextIndex;
int scc;
int vis[maxn];
int inStack[maxn];
stack<int> st;
int lo[maxn];
int hi[maxn];
vector<vll> comps;
int sz[maxn];
int step;

void clear(){
    for(int i=0; i<maxn; i++) vadj[i].clear();
    mp.clear();
    rev.clear();
    nextIndex=0;
    scc=0;
    while(!st.empty()) st.pop();
    comps.clear();
    for(int i=0; i<maxn; i++) vis[i]=0;
    step=0;
}



int tarjan(int x){
    if(vis[x]) return maxn+2;
    vis[x] = 1;
    inStack[x] = 1;
    st.push(x);
    lo[x] = hi[x] = step++;
    for(auto y : vadj[x]){
        if(inStack[y]){
            lo[x] = min(lo[x],hi[y]);
            continue;
        }
        lo[x] = min(lo[x], tarjan(y));
    }
    if(lo[x] == hi[x]){
        int currSz = 0;
        vll thisComp;
        while(st.top() != x){
            thisComp.push_back(st.top());
            inStack[st.top()] = 0;
            currSz++;
            st.pop();
        }
        thisComp.push_back(x);
        inStack[st.top()] = 0;
        st.pop();
        currSz++;
        comps.push_back(thisComp);
        sz[scc] = currSz;
        scc++;
    }
    return lo[x];
}

void add(string A){
    if(mp[A] != 0) return;
    mp[A] = ++nextIndex;
    rev[nextIndex] = A;
}

void solve(){
    cout << "Calling circles for data set " << ++T << ":\n";
    for(int i=0; i<M; i++){
        string a,b;
        cin >> a >> b;
        add(a);
        add(b);
        int ia=mp[a];
        int ib=mp[b];
        vadj[ia].insert(ib);
    }

    for(int i=1; i<=N; i++){
        if(!vis[i]) tarjan(i);
    }



    for(int i=0; i<scc; i++){
        int sizeComp = sz[i];
        for(int j=0; j<sizeComp; j++){
            cout << rev[comps[i][j]] << (j == sizeComp-1 ? "\n" : ", ");
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    T = 0;
    clear();
    while(1){
        cin>>N>>M;
        if(N == M && N == 0) return 0;
        if(T != 0) cout << '\n';
        solve();
        clear();
    }
}
