#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ll N;
    map<ll,ll> mp;
    map<ll,ll> mp2;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    vll vl(N);
    ll ans = 0;
    mp2[0]++;
    for(int i = 0; i < N; i++) cin >> vl[i];
    for(int i = 1; i < N; i++) vl[i] = vl[i]^vl[i-1];
    for(int i = 0; i < N; i+=2){
        ans+=mp[vl[i]];
        mp[vl[i]]++;
    }
    for(int i = 1; i < N; i+=2){
        ans+=mp2[vl[i]];
        mp2[vl[i]]++;
    }
    cout << ans << '\n';
}
