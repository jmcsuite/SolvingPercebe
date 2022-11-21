#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;
using tp = pair<pll, ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    ll N, M;
    cin >> N >> M;
    vll Fi(N+1);
    for(int i = 1; i <= N; i++) Fi[i] = i;
    vector<vll> vadj(N+1);
    vector<vll> cost(N+1);

    for(int i = 0; i<M;i++){
        ll a,b,c; cin>>a>>b>>c;
        vadj[a].push_back(b);
        cost[a].push_back(c);
        vadj[b].push_back(a);
        cost[b].push_back(c);
    }

    set<tp> st;
    tp a(pll(0,0), 1);
    st.insert(a);
    ll ans = 0;
    Fi[1] = 0;
    while(!st.empty()){
        tp x = *(st.begin());
        st.erase(st.begin());
        ll node = x.second;
        ll cos = x.first.second;
        ll it = x.first.first;
        if(Fi[node] == 1)  continue;
        //cout << node << endl;
        Fi[node] = 1;
        ans += cos*it;
        for(size_t i = 0; i < vadj[node].size(); i++){
            ll nex = vadj[node][i];
            //cout << nex << endl;
            if(Fi[nex] == 1) continue;
            //cout << nex << endl;
            tp b(pll(it+1, cost[node][i]), nex);
            st.insert(b);
        }
    }
    cout << ans << '\n';
}

