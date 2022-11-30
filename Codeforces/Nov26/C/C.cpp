#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    vll vl;
    while(T--){
        ll N; cin >> N;
        vl.resize(N); 
        for(int i = 0; i<N; i++) cin>>vl[i];
        sort(vl.begin(), vl.end());
        if(vl[0] == vl[N-1]){
            cout << N/2 << '\n';
            continue;
        }
        ll ans = 0;
        for(int i = 1; i < N;  i++){
            if(vl[i] != vl[i-1]) ans = max(ans, i*(N-i));
        }
        cout << ans << '\n';
    }
}
