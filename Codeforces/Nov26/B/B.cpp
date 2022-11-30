#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

ll gcd(ll a, ll b){
    if(a == 0) return b;
    if(b == 0) return a;
    return gcd(b%a, a);
}

int main(){
    ll T; cin >> T;
    while(T--){
        ll N; cin >> N;
        ll ans = 1;
        ll g; cin >> g;
        for(int i = 1; i<N; i++){
            ll a; cin >> a;
            g = gcd(a,g); 
            ans = a/g;
        }
        cout << ans << '\n';
    }
}