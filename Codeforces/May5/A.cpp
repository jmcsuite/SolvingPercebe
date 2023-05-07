#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N; cin>>N;
        vll vl(N+1);
        for(int i=0; i<N; i++){
            ll a; cin>>a; 
            for(int j=a; j<=N; j++) vl[j]++;
        }
        ll se=-1;
        for(int i=0; i<=N; i++){
            if(vl[i] == N-i) se=i;
        }
        cout << se << endl;
    }
}
