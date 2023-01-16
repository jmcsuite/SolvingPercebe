#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){

        ll N,M; cin>>N>>M;
        ll A = N;
        ll B = 1;
        while(A >= B){
            cout << A << ' ';
            A--;
            if(A < B) break;
            cout << B << ' '; 
            B++;
        }
        cout << '\n';
    }
}

