#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;
using item = pair<pll,ll>;

const int maxn=200000;

item vn[maxn];
item vm[maxn];
ll cn[maxn];
ll cm[maxn];


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N=0;
    ll M=0;
    ll Q; cin>>Q;
    while(Q--){
        ll a,b,c,d;
        cin>>a>>b>>c>>d;
        if(a==1){
            vm[M] = {{c-b,c+b},M};
            cm[M]= d;
            M++;
            continue;
        }
        vn[N] = {{c-b,c+b},N};
        cn[N] = d;
        N++;
    }

    sort(vn,vn+N, [&](item& a, item& b){
            if(a.first.second == b.first.second) return a.first.first < b.first.first;
            return a.first.second < b.first.second;
            });
    sort(vm,vm+M, [&](item& a, item& b){
            if(a.first.second == b.first.second) return a.first.first < b.first.first;
            return a.first.second < b.first.second;
            });

    ll ans=0;
    ll idx=0;
    set<item> st;
    for(int i=0; i<N; i++){
        //cout << i << ' ' << vn[i].first.first << ' ' << vn[i].first.second << ' ' << ans << endl;
        while(idx != M){
            if(vm[idx].first.second <= vn[i].first.second){
                st.insert(vm[idx]);
                idx++;
            }else{
                break;
            }
        }
        ll pi = vn[i].second;
        auto it=st.lower_bound({{vn[i].first.first,vn[i].first.first},0});
        while(1){
            if(it == st.end()) break;
            ll y = it->second;
            if(cm[y] > cn[pi]){
                ans+=cn[pi];
                cm[y]-=cn[pi];
                cn[pi]=0;
                break;
            }else{
                ans+=cm[y];
                it = st.erase(it);
                cn[pi] -= cm[y];
                cm[y] = 0;
            }
        }
        //cout << i << ' ' << vn[i].first.first << ' ' << vn[i].first.second << ' ' << ans << endl;
    }
    cout << ans << '\n';
}


    
        
        
