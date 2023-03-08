#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int maxn = 1e6+1;
int criba[maxn];
int sumAcum[maxn];

void build(){
    criba[0] = 1;
    criba[1] = 1;
    for(int i=2; i<maxn; i++){
        if(criba[i]) continue;
        for(int j=2; j*i<maxn; j++){
            criba[i*j] = 1;
        }
    }

    for(int i=2; i<maxn; i++){
        if(criba[i]) continue;
        sumAcum[i] = 1;
    }
    for(int i=1; i<maxn; i++) sumAcum[i]+=sumAcum[i-1];
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    build();
    while(T--){
        ll a,b; cin>>a>>b;
        ll ans = sumAcum[b];
        if(a) ans-=sumAcum[a-1];
        cout << ans << '\n';
    }
    return 0;
}
