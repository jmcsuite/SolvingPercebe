#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using sit = set<pll>::iterator;
const int maxn=5000;

ll happy[maxn];
ll duration[maxn];
map<pll,ll> mp;
set<pll> st;
ll N,M;
ll DP(sit it){
    if(it == st.end()) return 0;
    pll a = *it;
    if(a.second == N) return 0;
    if(mp[*it] != 0) return mp[*it];
    ll a1 = DP(++it);
    it--;
    ll a2 = happy[a.second];
    ll t2 = a.first+duration[a.second];
    auto itNext = st.lower_bound({t2,-1});
    a2 += DP(itNext);
    ll ans = max(a1,a2);
    mp[*it] = ans;
    return ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>M;
    for(int i=0; i<N; i++){
        ll a,b,c; cin>>a>>b>>c;
        happy[i] = a;
        duration[i] = b;
        for(int j=0;j<c;j++){
            ll x; cin>>x;
            st.insert({x,i});
        }
    }
    st.insert({M,N});
    ll ans = DP(st.begin());
    cout << ans << endl;
}


