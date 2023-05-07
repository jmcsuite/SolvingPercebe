#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;


const long long maxn=1000001;
ll crib[maxn];

void build(){
    crib[1]=1;
    for(ll i=2; i<maxn; i++){
        if(crib[i] != 0) continue;
        crib[i]=i;
        for(ll j=i; j*i<maxn; j++){
            if(crib[i*j] == 0) crib[i*j]=i;
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    build();
    for(int i=1; i<10; i++){
        //cout << crib[i] << ' ';
    }
    while(T--){
        ll N,M; cin>>N>>M;
        if(crib[N] <= M && N!=1){
            cout << "NO\n";
        }else{
            cout << "YES\n";
        }
    }
}
