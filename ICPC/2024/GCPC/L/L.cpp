#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<ll>;
using vpll = vector<pll>;

const int maxn = 7 + 2;
namespace Dinics {
    map<ll,ll> vadj[maxn];
    vpll layered[maxn];
    vpll layeredSum[maxn];
    int level[maxn];
    int index[maxn];
    const long long maxFlow = 1e16;
    void clear(int N) {
        for(int i = 0; i < N; i++) vadj[i].clear();
    }

    void buildLayered(int N, int S) {
        for (int i=0; i<N; i++) level[i]=-1;
        queue<int> q;
        queue<int> q2;
        int step=1;
        level[S]=0;
        q.push(S);
        while(1) {
            while(!q.empty()) {
                int x=q.front();
                q.pop();
                for(pll yy: vadj[x]) {
                    int y = yy.first;
                    if(level[y] != -1) continue;
                    if(yy.second <= 0) continue;
                    level[y] = step;
                    q2.push(y);
                }
            }
            if (q2.empty()) break;
            step++;
            while(!q2.empty()) {
                q.push(q2.front());
                q2.pop();
            }
        }

        for(int i=0; i<N; i++) {
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
            ll attempt = blockFlow(layered[x][i].first,nextFlow, T);
            if(attempt!=0) {
                layered[x][i].second-=attempt;
                if(layered[x][i].second==0) index[x]++;
                return attempt;
            }
        }
        return 0;
    }

    ll blockPaths(ll N,ll S, ll T){
        for(int i=0; i<N; i++) index[i]=0;
        ll ans=0;
        while(1){
            ll flow = blockFlow(S,maxFlow, T);
            ans+=flow;
            if(flow==0) return ans;
        }
    }

    ll dinics(ll N, ll S, ll T){
        ll ans=0;
        while(1){
            buildLayered(N,S);
            ll push = blockPaths(N,S,T);
            ans+=push;
            if(push==0) return ans;
            for(int i=0; i<N; i++){
                for(size_t j=0; j<layered[i].size(); j++) {
                    vadj[i][layered[i][j].first] = layered[i][j].second;
                    vadj[layered[i][j].first][i] += layeredSum[i][j].second-layered[i][j].second;
                }
            }
        }
    }
}

const int S = 0, T = 1, na = 2, nb = 3, nc = 4, nab = 5, nbc = 6, nac = 7, nabc = 8;
ll a,b,c,ab,bc,ac,abc;

void setup() {
    Dinics::clear(maxn);
    Dinics::vadj[S][nabc]=abc;
    Dinics::vadj[S][nac]=ac;
    Dinics::vadj[S][nab]=ab;
    Dinics::vadj[S][nbc]=bc;

    Dinics::vadj[nabc][na]=Dinics::maxFlow;
    Dinics::vadj[nabc][nb]=Dinics::maxFlow;
    Dinics::vadj[nabc][nc]=Dinics::maxFlow;

    Dinics::vadj[nab][na]=Dinics::maxFlow;
    Dinics::vadj[nab][nb]=Dinics::maxFlow;

    Dinics::vadj[nbc][nb]=Dinics::maxFlow;
    Dinics::vadj[nbc][nc]=Dinics::maxFlow;

    Dinics::vadj[nac][na]=Dinics::maxFlow;
    Dinics::vadj[nac][nc]=Dinics::maxFlow;

    Dinics::vadj[na][T]=a;
    Dinics::vadj[nb][T]=b;
    Dinics::vadj[nc][T]=c;
}

ll K;

ll solve() {
    int ans = 15;
    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j <= 5; j++) {
            for (int k = 0; k <= 5; k++) {
                if (i+j+k > 9) continue;
                if (i+j >= 8) continue;
                if (j+k >= 8) continue;
                if (i+k >= 8) continue;
                if (i+j+k >= ans) continue;
                if ((i+j+k)*K < ab+ac+bc+abc-a-b-c) continue;
                setup();
                Dinics::vadj[na][T] += i*K;
                Dinics::vadj[nb][T] += j*K;
                Dinics::vadj[nc][T] += k*K;
                if (Dinics::dinics(maxn,S,T) == (ab+ac+bc+abc)) ans = min(ans, i+j+k);
            }
        }
    }
    return ans;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        cin >> K;
        cin >> a >> b >> c >> ab >> bc >> ac >> abc;
        ll ans = 0;
        ans += (a+K-1)/K; a%=K; a = (K-a)%K;
        ans += (b+K-1)/K; b%=K; b = (K-b)%K;
        ans += (c+K-1)/K; c%=K; c = (K-c)%K;
        if (ab >= K) {ans += (ab-ab%K-K)/K; ab = K + ab%K;}
        if (ac >= K) {ans += (ac-ac%K-K)/K; ac = K + ac%K;}
        if (bc >= K) {ans += (bc-bc%K-K)/K; bc = K + bc%K;}
        if (abc >= 2*K) {ans += (abc-2*K-abc%K)/K; abc = 2*K + abc%K;}
        ans += solve();
        cout << ans << '\n';
    }
}
