#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=300000;
ll vl[maxn];
ll inp[maxn];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N; cin>>N;
        for(int i=0; i<N; i++){
            cin>>inp[i];
        }
        vl[0]=inp[0];
        ll M=1;
        for(int i=1; i<N; i++){
            if(inp[i] == inp[i-1]) continue;
            vl[M++]=inp[i];
        }

        ll ans=M;
        for(int i=1; i<M-1; i++){
            if(vl[i-1] < vl[i] && vl[i] < vl[i+1]) ans--;
            else if(vl[i-1] > vl[i] && vl[i] > vl[i+1]) ans--;
        }
        cout << ans << '\n';
    }
}

