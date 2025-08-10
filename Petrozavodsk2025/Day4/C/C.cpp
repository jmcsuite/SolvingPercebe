#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn = 500 * 3 + 1000 + 10;

namespace Dinics{
    map<ll,ll> vadj[maxn];
    vpll layered[maxn];
    vpll layeredSum[maxn];
    int level[maxn];
    int index[maxn];
    const long long maxFlow = 1e16;

    void clear(int N){
        for(int i=0; i<N; i++) vadj[i].clear();
    }

    void buildLayered(int N, int S){
        for(int i=0; i<N; i++) level[i] = -1;
        queue<int> q;
        queue<int> q2; //0-1 BFS
        int step = 1;
        level[S] = 0;
        q.push(S);
        while(1){
            while(!q.empty()){
                int x = q.front();
                q.pop();
                for(pll yy: vadj[x]){
                    int y = yy.first;
                    if(level[y] != -1) continue;
                    if(yy.second <= 0) continue;
                    level[y] = step;
                    q2.push(y);
                }
            }
            if(q2.empty()) break;
            step++;
            while(!q2.empty()){
                q.push(q2.front());
                q2.pop();
            }
        }

        for(int i=0; i<N; i++){
            layered[i].clear();
            layeredSum[i].clear();
            for(pll yy:vadj[i]){
                if(level[i]+1 != level[yy.first]) continue;
                layered[i].push_back(yy);
                layeredSum[i].push_back(yy);
            }
        }
    }

    ll blockFlow(int x, ll flow, int T){
        if(flow == 0) return flow;
        if(x == T) return flow;
        if(index[x] >= (ll)layered[x].size()) return 0;
        for(size_t i=index[x]; i<layered[x].size(); index[x]++,i=index[x]){
            ll nextFlow = min(flow, layered[x][i].second);
            ll attempt = blockFlow(layered[x][i].first, nextFlow, T);
            if(attempt!=0){
                layered[x][i].second-=attempt;
                if(layered[x][i].second == 0) index[x]++;
                return attempt;
            }
        }
        return 0;
    }

    ll blockPaths(ll N,ll S,ll T){
        for(int i=0; i<N; i++) index[i]=0;
        ll ans = 0;
        while(1){
            ll flow = blockFlow(S,maxFlow, T);
            ans+=flow;
            if(flow == 0) return ans;
        }
    }

    ll dinics(ll N, ll S, ll T){
        ll ans = 0;
        while(1){
            buildLayered(N,S);
            ll push = blockPaths(N,S,T);
            ans+=push;
            if(push == 0) return ans;
            // actualizar cambios en residual
            for(int i=0; i<N; i++){
                for(size_t j=0; j<layered[i].size(); j++){
                    vadj[i][layered[i][j].first] = layered[i][j].second;
                    vadj[layered[i][j].first][i] += layeredSum[i][j].second-layered[i][j].second;
                }
            }
        }
    }
}

int main() {
    ll n,m; cin>>n>>m;
    n--;
    ll a = n;
    ll b = n;
    ll c = n;

    ll s = a+b+c+m;
    ll t = s + 1;
    vll A(n); 
    vll B(n+1);
    vll C(n);
    for (int i=0; i<n; i++) cin>>A[i];
    for (int i=0; i<=n; i++) cin>>B[i];
    for (int i=0; i<n; i++) cin>>C[i];

    for (int i=0; i<n; i++) {
        Dinics::vadj[s][i] = A[i];
        Dinics::vadj[i+a+b][t] = C[i] + B[i];
        if (i + 1 < n) Dinics::vadj[i+a+b][t] += B[i+1];
        Dinics::vadj[i][i+a+b] = Dinics::maxFlow;
    }
    Dinics::vadj[s][n-1] += B[n];

    for (int i=1; i<n; i++) {
        Dinics::vadj[s][i+a] = 2*B[i];
        Dinics::vadj[i+a][i+a+b] = Dinics::maxFlow;
        Dinics::vadj[i+a][i+a+b-1] = Dinics::maxFlow;
    }

    ll ans = 0;
    for (int i=1; i<n; i++) ans += 2*B[i];
    ll x = a+b+c;
    while (m--) {
        ll i,j,k; cin>>i>>j>>k;
        i--; j--;
        ans += k;
        Dinics::vadj[s][x] = k;
        Dinics::vadj[x][i+a+b] = Dinics::maxFlow;
        Dinics::vadj[x][j+a+b] = Dinics::maxFlow;
        Dinics::vadj[j+a+b][t] += k;
        x++;
    }

    ans = Dinics::dinics(t+1,s,t) - ans;
    cout << ans << '\n';
}
