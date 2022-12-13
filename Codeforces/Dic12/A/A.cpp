#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ll T; cin >> T;
    while(T--){
        ll N; cin >> N;
        ll ans = 0;
        for(int i = 1; i <= 9; i++){
            ll x = i;
            while(x <= N){
                ans++;
                x*=10;
            }
        }
        cout << ans << '\n';
    }
}
