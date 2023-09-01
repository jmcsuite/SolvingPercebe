#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,Q; cin>>N>>Q;
    vll vl(N); for(int i=0; i<N; i++) cin>>vl[i];

    for(int i=1; i<N; i++) vl[i] = vl[i] ^ vl[i-1];

    auto sum = [&](ll a, ll b){
        if(a == 0) return vl[b];
        return vl[b] ^ vl[a-1];
    };

    while(Q--){
        ll a,b; cin>>a>>b; a--; b--;
        cout << sum(a,b) << '\n';
    }
}
