#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

using map_t = tree<pll, null_type, less<pll>,
      rb_tree_tag, tree_order_statistics_node_update>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    ll N,Q; cin>>N>>Q;
    vll vl(N); for(int i=0; i<N; i++) cin>>vl[i];

    map_t st;
    for(int i=0; i<N; i++) st.insert({vl[i],i});

    while(Q--){
        char q; cin>>q;
        if(q == '?'){
            ll a,b; cin>>a>>b;
            ll up = st.order_of_key({b,N});
            ll down = st.order_of_key({a,-1});
            cout << up-down << '\n';
            continue;
        }
        ll k,x; cin>>k>>x;
        k--;

        st.erase({vl[k],k});
        vl[k]=x;
        st.insert({vl[k],k});
    }
}




