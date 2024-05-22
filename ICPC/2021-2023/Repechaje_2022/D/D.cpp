#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

using map_t = tree<pll,null_type,
      less<pll>, rb_tree_tag,
      tree_order_statistics_node_update>;

const int maxn=100000;
ll vl[maxn];

int main(){
    map_t mp;
    ll M; cin>>M;
    for(int i=0; i<M; i++){
        ll q; cin>>q;
        if(q==1){
            ll b; cin>>b;
            vl[i]=b;
            mp.insert({b,i});
            continue;
        }
        if(q==2){
            ll a; cin>>a; a--;
            ll b = vl[a];
            mp.erase({b,a});
            continue;
        }
        if(q==3){
            ll a; cin>>a; a--;
            ll x; cin>>x;
            ll b = vl[a];
            mp.erase({b,a});
            vl[a]+=x;
            mp.insert({b+x,a});
            continue;
        }
        if(q==4){
            ll a; cin>>a; a--;
            ll b = vl[a];
            cout << mp.order_of_key({b,-1}) << endl;
        }
    }
}


      
