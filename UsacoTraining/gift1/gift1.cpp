/*
ID: jmcsuit1 
LANG: C++14
TASK: gift1
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=10;
ll sol[maxn];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("gift1.in", "r", stdin);
    freopen("gift1.out", "w", stdout);
    ll N; cin>>N;
    map<string,ll> mp;
    map<ll,string> rev;
    for(int i=0; i<N; i++){
        string a; cin>>a;
        mp[a]=i; sol[i]=0;
        rev[i]=a;
    }
    for(int xx=0; xx<N; xx++){
        string a; ll i;
        cin>>a;
        i=mp[a];
        ll C,M; cin>>C>>M;
        sol[i]-=C;
        ll cc=0; 
        if(M!=0){
            cc=C/M;
            sol[i]+=C%M;
        }else{
            sol[i]+=C;
        }
        for(int j=0; j<M; j++){
            string nex; cin>>nex;
            ll nn=mp[nex];
            sol[nn]+=cc;
        }
    }
    for(int i=0; i<N; i++){
        cout << rev[i] << ' ' << sol[i] << '\n';
    }
}
    



