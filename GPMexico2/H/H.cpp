#include <bits/stdc++.h>
#define LSONE(x) ((x)&(-x))
using namespace std;
using ll = long long;
using vll = vector<ll>;

ll gcd(ll a, ll b){
    if(a == 0) return b;
    if(b == 0) return a;
    return gcd(b%a, a);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M;
    cin >> N >> M;
    vll vl(N);
    for(int i = 0; i < N; i++) cin>>vl[i];
    vll dp((ll(1) << N));

    ll ans = 0;
    for(ll i = 1; i < (ll(1) << N); i++){
        ll m = 1;
        if(__builtin_popcountll(i) == 1) m = vl[__builtin_ctzll(i)];
        else{
            ll pre = i-LSONE(i);
            ll nex = __builtin_ctzll(i);
            m = (dp[pre]*vl[nex])/gcd(dp[pre],vl[nex]);
        }
        dp[i] = m;
        //cout << i << ' ' << m << endl; 
        if(__builtin_popcountll(i) % 2) ans += M/m;
        else ans -= M/m;
    }
    cout << ans << '\n';
}
