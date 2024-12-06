#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<ll>;
using vpll = vector<pll>;

const int maxn = 2e5+2;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin>>N>>M;
    vll vl(N); for(int i=0; i<N; i++) cin>>vl[i];
    set<ll> st;
    map<ll,ll> mp;
    for(int i=0; i<M; i++){
        ll a; cin>>a;
        st.insert(a);
        mp[a]=i;
    }
    vpll ans(M);
    for(int i=0; i<M; i++){
        ans[i].first = -1;
        ans[i].second = -1;
    }
    for(int i=0; i<N; i++){
        ll tim=0;
        while(tim < maxn){
            auto it=st.lower_bound(tim-i);
            if(it == st.end() || *it+i >= tim+vl[i]){
                tim+=vl[i];
                tim+=vl[i];
                continue;
            }
            ll idx = mp[*it];
            ans[idx].first = i;
            ans[idx].second = i+*it;
            tim = *it+i+1;
            tim+=vl[i];
            st.erase(it);
        }
    }
    for(int i=0; i<M; i++){
        cout << ans[i].first << ' ' << ans[i].second << '\n';
    }
}
