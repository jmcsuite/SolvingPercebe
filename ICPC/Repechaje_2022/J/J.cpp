#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vadj = vector<vll>;

void DFS(ll x, ll px, vadj& adj, vll& vl){
    vl[x] = px;
    for(size_t i = 0; i < adj[x].size(); i++){
        if(adj[x][i] == px) continue;
        DFS(adj[x][i], x, adj, vl);
    }
}

ll get(ll x, ll dx, vadj& adj, vll& vl, vll& uno, vll& tres, vll& w, multiset<ll>& st, ll sum){
    ll it = 0;
    ll ans = w[it+dx]+sum;
    for(auto stit = st.rbegin(); stit != st.rend(); stit++){
        it++;
        sum += *stit;
        ans = max(ans, w[it+dx]+sum);
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    vll w(N+1);
    for(int i = 0; i < N; i++) cin >> w[i];
    w[N] = 1e15;
    vll vl(N);
    vadj adj(N);
    for(int i = 0; i < N-1; i++){
        ll a,b; cin>>a>>b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    DFS(0, 0, adj, vl);
    queue<int> q;
    vll uno(N);
    vll cero(N);
    vll tres(N);

    for(int i = 1; i < N; i++) if(adj[i].size() == 1) q.push(i);

    vll cc(N);
    for(int i = 1; i < N; i++) cc[i] = adj[i].size() - 1;
    cc[0] = adj[0].size();
    ll ans = 0;
    while(!q.empty()){
        int x = q.front();
        q.pop();
        if(x != 0){
            cc[vl[x]]--;
            if(cc[vl[x]] == 0) q.push(vl[x]);
        }
        ll sum = 0;
        multiset<ll> st;
        for(int i = 0; i < adj[x].size(); i++){
            if(adj[x][i] == vl[x]) continue;
            sum += uno[adj[x][i]];
            st.insert(tres[adj[x][i]]);
        }
        cero[x] = get(x, 0, adj, vl, uno, tres, w, st, sum);
        uno[x] = get(x, 1, adj, vl, uno , tres, w, st, sum);
        tres[x] = cero[x]-uno[x];
    }
    cout << cero[0] << '\n';
}
