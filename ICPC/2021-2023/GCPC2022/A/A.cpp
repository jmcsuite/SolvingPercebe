#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=1000001;

map<ll,bool> has;
map<ll,ll> sqr;


int main(){
    ios::sync_with_stdio(0);
    for(ll i=0; i<maxn; i++){
        ll j = i*i; 
        has[j] = true;
        sqr[j] = i;
    }

    ll a,b; cin>>a>>b;
    a--; b--;
    ll ans=1;
    for(ll i = a-1; i> 0; i--){
        ll di = a*a - i*i;
        if(!has[di]) continue;
        di = sqr[di];
        ll j = i*b;
        if(j % a != 0) continue;
        ll dj = di*b;
        if(dj % a != 0) continue;
        ans++;
        //cout << i << ' ' << di << ' ' << j << ' ' << dj << endl;
    }

    if(a != b) ans*= 2;
    cout << ans << '\n';
    return 0;
}
