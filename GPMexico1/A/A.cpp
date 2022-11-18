#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<long long>;
ll maxk = 50;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    vll input(N);
    for(int i=0; i<N; i++) cin>>input[i];
    vll bitCount(maxk);
    for(ll i = 0; i < maxk; i++){
        for(ll j = 0; j < N; j++){
            if(input[j]&(ll(1) << i)) bitCount[i]++;
        }
    }
    
    ll mask = 0;
    ll anmask = 0;
    for(ll i = 0; i < maxk; i++) {
        bitCount[i]%=2;
        if(bitCount[i] == 0) mask = mask | (ll(1) << i);
        else anmask = anmask | (ll(1) << i);
    }
    for(int i = 0; i<N; i++) input[i] = input[i]&mask;
    vll basis(maxk);

    for(int i = 0; i<N; i++){
        ll num = input[i];
        for(ll j = maxk-1; j >= 0; j--){
             if((num & (ll(1) << j)) == 0) continue;
             if(basis[j] == 0){
                basis[j] = num;
                break;
             }
             num = num^basis[j];
        }
    }

    ll maxXor = 0;
    for(int j = maxk-1; j >= 0; j--) maxXor = max(maxXor^basis[j], maxXor);
    maxXor &= mask;
    maxXor *= 2;
    maxXor += anmask;
    cout << maxXor  << '\n';
}

    