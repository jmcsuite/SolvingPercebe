#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vii = vector<int>;

void DFS(ll x, ll p, vector<vii>& vadj, vii& par){
    //cout << x << endl;
    par[x]  = p;
    for(size_t i = 0; i < vadj[x].size(); i++){
        if(vadj[x][i] == par[x]) continue;
        DFS(vadj[x][i], x, vadj, par);
    }
}

void BFS(int x, set<int>& st, vii& vis, vii& par, vector<vii>& vadj, int K){
    int org = x;
    queue<pair<int,int>> q;
    q.push(pair<int,int>(x,0));
    while(!q.empty()){
        pair<int, int> xx = q.front();
        x = xx.first;
        int pr = xx.second;
        //cout << x << ' ' << pr << ' ' << vis[x] << endl;
        q.pop();
        if(vis[x] == -1 && x != 0) st.insert(x);
        if(vis[x] != -1 && vis[x] <= pr) continue;
        vis[x] =  pr;
        if(vis[x] == K) continue;
        for(size_t i = 0; i < vadj[x].size(); i++){
            q.push(pair<int,int>(vadj[x][i] , pr + 1));
        }
    }
}





int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N, K;
    cin>>N>>K;
    vii par(N);
    vector<vii> vadj(N);
    for(int i=0; i<N-1; i++){
        ll a, b;
        cin>>a>>b;
        a--;
        b--;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
    }
 
    DFS(0,0,vadj,par);
    //return 0;
    vii vis(N, -1);
    set<int> st;
    st.insert(0);
    
    while(!st.empty()){
        int a = *st.begin();
        st.erase(st.begin());
        
        BFS(a, st, vis,par, vadj, K);
        
        cout << a+1 << (st.empty() ? '\n' : ' ');
    }
}