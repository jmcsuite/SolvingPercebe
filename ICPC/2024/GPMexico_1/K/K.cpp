#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn = 25*25*2 + 2;
int chess[25][25];

namespace Dinics {
    map<ll, ll> vadj[maxn];
    vpll layered[maxn];
    vpll layeredSum[maxn];
    int level[maxn];
    int index[maxn];
    const long long maxFlow = 1e16;

    void clear(int N) {
        for(int i=0; i<N; i++) vadj[i].clear();
    }

    void buildLayered(int N, int S) {
        for(int i=0; i<N; i++) level[i] = -1;
        queue<int> q;
        queue<int> q2;
        int step = 1; 
        level[S] = 0;
        q.push(S);
        while(1) {
            while(!q.empty()) {
                int x = q.front();
                q.pop();
                for(pll yy: vadj[x]) {
                    int y = yy.first;
                    if(level[y] != -1) continue;
                    if(yy.second <= 0) continue;
                    level[y] = step;
                    q2.push(y);
                }
            }
            if(q2.empty()) break;
            step++;
            while(!q2.empty()) {
                q.push(q2.front());
                q2.pop();
            }
        }

        for (int i=0; i<N; i++) {
            layered[i].clear();
            layeredSum[i].clear();
            for(pll yy:vadj[i]){
                if(level[i]+1 != level[yy.first]) continue;
                layered[i].push_back(yy);
                layeredSum[i].push_back(yy);
            }
        }
    }

    ll blockFlow(int x, ll flow, int T) {
        if (flow == 0) return flow;
        if (x == T) return flow;
        if (index[x] >= (ll)layered[x].size()) return 0;
        for(size_t i=index[x]; i<layered[x].size(); index[x]++,i=index[x]){
            ll nextFlow = min(flow, layered[x][i].second);
            ll attempt = blockFlow(layered[x][i].first, nextFlow, T);
            if (attempt != 0) {
                layered[x][i].second-=attempt;
                if (layered[x][i].second == 0) index[x]++;
                return attempt;
            }
        }
        return 0;
    }

    ll blockPaths(ll N, ll S, ll T) {
        for (int i=0; i<N; i++) index[i]=0;
        ll ans = 0;
        while(1) {
            ll flow = blockFlow(S, maxFlow, T);
            ans+=flow;
            if(flow == 0) return ans;
        }
    }

    ll dinics(ll N, ll S, ll T) {
        ll ans = 0;
        while(1) {
            buildLayered(N, S);
            ll push = blockPaths(N, S, T);
            ans+=push;
            if(push == 0) return ans;

            for (int i=0; i<N; i++) {
                for(size_t j=0; j<layered[i].size(); j++) {
                    vadj[i][layered[i][j].first] = layered[i][j].second;
                    vadj[layered[i][j].first][i] += layeredSum[i][j].second-layered[i][j].second;
                }
            }
        }
    }
}

int dx[8] = {1, 1, 2, 2, -1, -1, -2, -2};
int dy[8] = {2, -2, 1, -1, 2, -2, 1, -1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, K; cin >> N >> K; 
    for (int i = 1; i <= K; i++) {
        ll a, b; cin >> a >> b; a--; b--;
        chess[a][b] = i;
    }

    Dinics::clear(2*K+2);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(chess[i][j] == 0) continue;

            for(int k = 0; k < 8; k++) {
                ll ni = i+dx[k];
                ll nj = j+dy[k];
                if(ni < 0 || ni >= N) continue;
                if(nj < 0 || nj >= N) continue;
                if (chess[ni][nj] == 0) continue;
                Dinics::vadj[chess[i][j]][chess[ni][nj]+K] = 1;
            }
        }
    }

    ll S = 0; 
    ll T = 2*K+1;

    for (int i = 1; i <= K; i++) Dinics::vadj[S][i] = 1;
    for (int i = 1; i <= K; i++) Dinics::vadj[i+K][T] = 1; 
    cout << Dinics::dinics(2*K+2, S, T)/2 << '\n';
}
