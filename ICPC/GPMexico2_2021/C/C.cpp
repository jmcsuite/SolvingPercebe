#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        string s; cin>>s;
        ll N = s.size();
        vll vl(N);
        for(size_t i=0; i<s.size(); i++){
            vl[i] = (s[i] == 'R' ? -1 : 1);
        }
        ll ans = 0;
        ll acum = 0;
        for(int i=0; i<N; i++){
            acum+=vl[i];
            if(acum < 0){
                ans = i+1;
                acum=0;
            }
        }
        cout << ans << '\n';
    }
}
