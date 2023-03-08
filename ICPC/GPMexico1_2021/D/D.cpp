#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    vector<vll> vadj(N);
    for(int i=0; i<N; i++) vadj[i].resize(4);
    for(int i=0; i<N; i++){
        for(int j=0; j<4; j++) cin>>vadj[i][j];
    }

    set<pll> st;
    for(int i=0; i<N; i++) st.insert({0,i});
    set<pll> next;
    for(int j=0; j<4; j++){
        ll t=0;
        for(int i=0; i<N; i++){
            pll aa = *st.begin();
            //cout << aa.first << ' ' << aa.second << endl;
            st.erase(st.begin());
            if(vadj[aa.second][j] == 0){
                next.insert(aa);
                continue;
            }
            t=max(aa.first,t);
            t+=vadj[aa.second][j];
            next.insert({t, aa.second});
        }
        swap(st,next);
    }

    ll ans = st.rbegin()->first;
    cout << ans << '\n';
}
        
