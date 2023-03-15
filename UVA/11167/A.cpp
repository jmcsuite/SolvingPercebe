#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn = 400;

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
        if(index[x] >= layered[x].size()) return 0;
        ll ans = 0;
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


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    const int maxTime = 50001;
    ll N,OUT;
    ll Q = 0;
    while(1){
        cin>>N;
        if(N == 0) return 0;
        cin >> OUT;
        ll nNodes = 0;
        Dinics::clear(maxn);
        vector<vll> vadj(maxTime);
        ll maxPosFlow = 0;
        ll S,T;
        S = 0;
        T = maxn-1;
        for(int i=1; i<=N; i++){
            ll V,A,B;
            cin>>V>>A>>B;
            // agregar de source a A
            Dinics::vadj[S][i]+=V;
            //
            //cout << "ADDING EDGE FROM: " << S << " To " << i << " With Capacity " << V << endl;
            maxPosFlow+=V;
            vadj[A].push_back(i);
            vadj[B].push_back(-1*i);
        }
        ll cc = 0;
        set<ll> st;
        ll node = N+1;
        map<ll,ll> fini;
        map<ll,ll> time;
        map<ll,ll> cant;
        map<ll,ll> cantMax;
        map<ll,ll> iniTime;
        map<ll,ll> finito;
        for(int i=0; i<maxTime; i++){
            if(vadj[i].size() == 0){
                cc += OUT;
                continue;
            }
            for(ll x: st){
                Dinics::vadj[x][node]+=(cc/OUT);
                //cout << "ADDING EDGE FROM: " << x << " To " << node << " With Capacity " << cc/OUT << endl;
            }
            Dinics::vadj[node][T]+=cc;
            cantMax[node]=OUT;
            time[node]=i-cc/OUT;
            finito[node]=i;
            //cout << "ADDING EDGE FROM: " << node  << " To " << T  << " With Capacity " << cc << endl;
            cc = OUT;
            for(int x: vadj[i]){
                if(x > 0) st.insert(x);
                if(x < 0) st.erase(-1*x);
            }
            node++;
            iniTime[node]=i;
        }
        //cout << "NUMBER OF NODES: " << node << endl;
        ll maxFlow = Dinics::dinics(maxn,S,T);
        cout << "Case " << ++Q << ": ";
        //cout << maxFlow << endl;
        if(maxFlow != maxPosFlow){
            cout << "No" << '\n';
            continue;
        }
        cout << "Yes" << '\n';
        vector<vpll> ans(N);
        for(int i=1; i<=N; i++){
            for(pll yy: Dinics::vadj[i]){
                if(Dinics::vadj[yy.first][i] == 0) continue;
                ll j = Dinics::vadj[yy.first][i];
                ll fini = finito[yy.first];
                ll tt = time[yy.first];
                ll ttOrg = tt;
                ll rfini = min(tt+j, fini);
                if(yy.first == 14){
                    //cout << "14 AAAA: " << tt << ' ' << fini << ' ' << j << endl;
                }
                j -= (rfini-tt);
                tt = rfini;
                if(tt == fini) tt = iniTime[yy.first];
                
                time[yy.first]=tt;
                if(j == 0){
                    ans[i-1].push_back({ttOrg,rfini});
                    continue;
                }
                ans[i-1].push_back({tt,tt+j});
                ans[i-1].push_back({ttOrg,rfini});
                time[yy.first] =tt+j;
            }
        }
        vector<vpll> ans2(N);
        for(int i=0; i<N; i++){
            ll ini=0;
            ll prev=0;
            if(ans[i].size()>0) ini=ans[i][0].first;
            for(int j=0; j<ans[i].size(); j++){
                if(j != 0 && ans[i][j].first != prev){
                    ans2[i].push_back({ini,prev});
                    ini=ans[i][j].first;
                }
                prev = ans[i][j].second;
            }
            ans2[i].push_back({ini,prev});
        }

        for(int i=0; i<N; i++){
            cout << ans2[i].size() << " ";
            for(size_t j=0; j < ans2[i].size(); j++){
                cout << "(" << ans2[i][j].first << "," << ans2[i][j].second << ")" << (j == ans2[i].size()-1 ? '\n' : ' ');
            }
        }
    }
}
