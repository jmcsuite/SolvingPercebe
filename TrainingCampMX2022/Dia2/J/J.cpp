#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll N,M;

void solve(ll a,ll b){
    if(a == b){
        ll ini = 1;
        ll fin = M;
        while(ini < fin){
            cout << a << ' ' << ini << '\n';
            cout << b << ' ' << fin << '\n';
            ini++;fin--;
        }
        if(ini == fin){
            cout << a << ' ' << ini << '\n';
        }
    }else{
        ll ini = 1;
        ll fin = M;
        while(ini < M+1){
            cout << a << ' ' << ini << '\n';
            cout << b << ' ' << fin << '\n';
            ini++;fin--;
        }
    }
    return;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>M;
    ll i = 1;
    ll j = N;
    while(i<=j){
        solve(i,j);
        i++;
        j--;
    }
}
