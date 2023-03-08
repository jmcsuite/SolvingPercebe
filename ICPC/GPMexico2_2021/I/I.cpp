#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll reduce(ll x){
    if(x == 0) return 0;
    ll ans=1;
    while(x){
        ans*=x%10;
        x/=10;
    }
    return ans;
}

ll solve(ll x){
    ll ans = 0;
    while(x != reduce(x)){
        x = reduce(x);
        ans++;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll a; cin>>a;
        a = solve(a);
        cout << a << '\n';
    }
}
