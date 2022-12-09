#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;


namespace seg{
    ll m; const int maxn = 5e5+10;
    pll st[2*maxn];
    void build(ll n, vector<pll>& vl){
        m = n;
        for(int i = n; i < 2*n; i++) st[i] = vl[i-n];
        for(int i = n-1; i > 0; i--) st[i] = max(st[i*2],st[i*2+1]);
    }

    pll query(ll l, ll r){
        l+=m; r+=m; 
        pll ans = pll(-1,-1);
        for(;l<r;l/=2,r/=2) {
            if(l&1) ans = max(ans, st[l++]);
            if(r&1) ans = max(ans, st[--r]);
        }
        return ans;
    }
}
    
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll N; cin>>N;
    vector<pll> vl(N);
    vll izq(N);
    vll der(N);
    for(int i = 0; i < N; i++) cin >> vl[i].first;
    for(int i = 0; i < N; i++) vl[i].second = i;
    stack<pll> st;
    st.push(pll(1e9, -1));
    for(int i = 0; i < N; i++){
        while(vl[i] >= st.top()) st.pop();
        izq[i] = st.top().second;
        st.push(vl[i]);
    }

    while(!st.empty()) st.pop();
    st.push(pll(1e9, N));
    for(int i = N-1; i >= 0; i--){
        while(vl[i] >= st.top()) st.pop();
        der[i] = st.top().second;
        st.push(vl[i]);
    }
    
    seg::build(N, vl);
    ll T; cin >> T;
    while(T--){
        ll ans = 0;
        ll M; cin >> M;
        vll q(M);
        for(int i = 0; i < M; i++){
            cin >> q[i];
            q[i]--;
        }

        auto busq_inv = [&](ll x){
            ll ini = -1;
            ll inc = M/2+1;
            while(inc > 0){
                if(ini + inc < M && q[ini + inc] <= x) ini+= inc;
                else inc/=2;
            }

            return ini;
        };

        auto busq_bin = [&](ll x){
            ll ini = M;
            ll inc = M/2*-1 - 1;
            while(inc < 0){
                if(ini + inc >= 0 && q[ini + inc] >= x) ini+=inc;
                else inc/=2;
            }
            return ini;
        };
        
        unordered_set<ll> uset;
        for(int i = 0; i < M; i++) uset.insert(q[i]);
        for(int i = 1; i < M; i++){
            pll mini = seg::query(q[i-1], q[i]+1);
            uset.insert(mini.second);
        }

        for(auto it = uset.begin(); it != uset.end(); it++){
            ll x = *it;
            ll qder = busq_inv(der[x]-1);
            ll qizq = busq_bin(izq[x]+1);
            ll qj = busq_bin(x);
            ll qi = busq_inv(x);
            ll toizq = qi-qizq+1;
            ll toder = qder-qj+1;
            ans += toizq*toder*vl[*it].first;
        }

        cout << ans << '\n';
    }
}
