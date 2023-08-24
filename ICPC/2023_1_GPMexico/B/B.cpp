#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N,K,L;
    cin>>N>>K>>L;

    ll ans = (N*K) / L;
    if((N*K)%L != 0) ans++;
    cout << ans << '\n';
}
