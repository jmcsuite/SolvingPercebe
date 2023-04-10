#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N,M;
        cin>>N>>M;
        ll a,b,c,d;
        cin>>a>>b>>c>>d;
        if(a == N) a = 1;
        if(b == M) b = 1;
        if(c == N) c = 1;
        if(d == M) d = 1;

        if(a == b && a == 1){
            cout << 2 << '\n';
            continue;
        }
        if(c == 1 && c == d){
            cout << 2 << '\n';
            continue;
        }
        if(a == 1 || b == 1 || c == 1 || d == 1){
            cout << 3 << '\n';
            continue;
        }
        cout << 4 << '\n';
    } 
}
