#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,a,b; cin>>N>>a>>b;
    cout << (N-__builtin_ctzll(a)-1) << '\n';
}