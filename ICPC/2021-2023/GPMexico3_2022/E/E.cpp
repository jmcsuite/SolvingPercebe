#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    vll vl(N);
    for(int i =0; i <N; i++) cin>>vl[i];
    map<ll,ll> mp;
    ll ans = 0;
    for(int i = 0; i<N; i++){
        if(mp[vl[i]] <= 0){
            ans++;
            mp[vl[i]] = 1;
        }
        mp[vl[i]]--;
        mp[vl[i]-1]++;
    }
    cout << ans << '\n';
}