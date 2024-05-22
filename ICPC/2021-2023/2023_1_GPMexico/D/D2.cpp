#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<ll>;

using map_t = tree<pll, null_type, less<pll>, rb_tree_tag,
      tree_order_statistics_node_update>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,Q; cin>>N>>Q;
    ll it=0;

    map_t mp;
    //multiset<ll> st;

    for(int i=0; i<N; i++){
        ll a; cin>>a;
        mp.insert({a,it++});
    }

    while(Q--){
        ll q; cin>>q;
        if(q == 2){
            ll a,b; cin>>a>>b;
            ll ans = mp.order_of_key({b, it+1});
            ans -= mp.order_of_key({a, -1});
            cout << ans << '\n';
            continue;
        }
        ll k; cin>>k;
        if(mp.lower_bound({k,0}) != mp.end() && mp.lower_bound({k,0})->first == k) continue;
        if(mp.rbegin()->first < k){
            mp.insert({k,it++});
            continue;
        }
        auto it3 = mp.lower_bound({k+1, 0});
        mp.erase(it3);
        mp.insert({k, it++});
    }
}
        

