#include <bits/stdc++.h>

using namespace std; 
#define UNVISITED 0

vector<int> dfs_num, dfs_low, S, visited;
vector<vector<int>> AdjList;
int dfsNumberCounter;
int n, m, numSCC;
unordered_map<int, int> components;

void tarjanSCC(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
    S.push_back(u);
    visited[u] = 1;
    for(int j = 0; j < (int)AdjList[u].size(); j++) {
        auto v = AdjList[u][j];
        if(dfs_num[v] == UNVISITED)
            tarjanSCC(v);
        if(visited[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if(dfs_low[u] == dfs_num[u]) {
        numSCC++;
        while(1) {
            int v = S.back(); S.pop_back(); visited[v] = 0;
            components[v] = numSCC;
            if(u==v) break;
        }
    }

}
typedef long long ll;
typedef vector<ll> vll;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;
    AdjList.resize(n + 1);
    for(int i = 0; i < m; i++) {
        int x, y;
        cin>>x>>y;
        AdjList[x].push_back(y);
    }

    dfs_num.assign(n+1, UNVISITED); dfs_low.assign(n+1, 0); visited.assign(n+1, 0);
    dfsNumberCounter = numSCC = 0;
    for(int i = 1; i <= n; i++) {
        //cout << i << ' ' << numSCC << endl;
        if(dfs_num[i] == UNVISITED) tarjanSCC(i); 
    }
    

    vll in;
    vll out;

    in.resize(numSCC+1);
    out.resize(numSCC+1);
    
    for(int i = 1; i<= n; i++){
        for(size_t j = 0; j < AdjList[i].size(); j++){
            ll pa = components[i];
            ll pb = components[AdjList[i][j]];
            if(pa == pb) continue;
            in[pb]++;
            out[pa]++;
        }
    }
    
    

     
    ll a1 = 0;
    ll a2 = 0;
    for(int i = 1; i < numSCC+1; i++){
        if(in[i] == 0) a1++;
        if(out[i] == 0) a2++;
    }

    if(numSCC == 1) {
        cout << 0 << endl;
        return 0;
    }
    cout << max(a1,a2) << endl;

}