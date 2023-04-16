#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=2000;

ll h[maxn];
set<ll> st[maxn];

ll N;

void build(ll x){
    st[x].clear();
    if(x == N-1) return;
    ll hPrev=h[x+1]-h[x];
    ll xPrev=1;
    st[x].insert(x+1);
    for(int i=x+2; i<N; i++){
        if((h[i]-h[x])*xPrev >= hPrev*(i-x)){
            st[x].insert(i);
            hPrev = h[i]-h[x];
            xPrev = i-x;
        }
    }
}

void quitar(ll x, ll k){
    ll ans = 0;
    auto res = st[k].insert(x);
    if(res.second == true){
        //cout << "HELLO THERE" << endl;
        if(res.first == st[k].begin()){
            ans++;
            //cout << "SHOULD NOT" << endl;
        }else{
            //cout << "YESSS " << x << ' ' << k << endl;
            res.first--;
            ll y = *(res.first);
            if((h[y]-h[k])*(x-k) > (h[x]-h[k])*(y-k)){
                //cout << "BEING ERASED " << x << ' ' << k << ' ' << y << endl;
                st[k].erase(x);
                return;
            }
            ans++;
            res.first++;
        }
    }

    res.first++;
    auto it=res.first;
    while(it != st[k].end()){
        ll y = *it;
        if((h[x]-h[k])*(y -k) > (h[y]-h[k])*(x-k)){
            it = st[k].erase(it);
            ans--;
        }else{
            break;
        }
    }
    return;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N;
    for(int i=0; i<N; i++) cin>>h[i];
    for(int i=0; i<N; i++) build(i);
    
    ll Q; cin>>Q;
    while(Q--){
        ll x,y;
        cin>>x>>y; x--;
        h[x]+=y;
        build(x);
        for(int i=0; i<x; i++){
            quitar(x,i);
        }
        ll ans = 0;
        for(int i=0; i<N; i++) ans+=st[i].size();
        cout << ans << '\n';
    }
}

