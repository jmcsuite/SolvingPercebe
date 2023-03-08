#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

string solve(ll k){
    if(k==1) return "2";
    if(k%2){
        string ans = "(2*";
        ans += solve(k-1);
        ans+=")";
        return ans;
    }
    string ans = "("+solve(k/2)+")^2";
    return ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N; cin>>N;
        cout << solve(N) << '\n';
    }
}
