#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=10;



ll ans[maxn];

void clear(){
    for(int i=0; i<maxn; i++) ans[i]=-1;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        clear();
        ll N; cin>>N;
        for(int i=0; i<N; i++){
            ll a,b;
            cin>>a>>b;
            b--;
            ans[b]=max(a, ans[b]);
        }
        bool se=true;
        for(int i=0; i<maxn; i++){ if(ans[i] == -1) se=false;}
        if(!se){
            cout << "MOREPROBLEMS\n";
            continue;
        }
        ll aaa=0;
        for(int i=0; i<maxn; i++) aaa+=ans[i];
        cout << aaa << '\n';
    }
}
            
