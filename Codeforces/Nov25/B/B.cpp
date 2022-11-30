#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<long long>;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while(T--){
        ll N; cin >> N;
        
        if(N%2==1){
            for(int i = 0; i<N; i++) cout << 1 << (i == N-1 ? '\n' : ' ');
            continue;
        }
        if(N%4==2){
            for(int i = 0; i<N; i+=2) cout << 1 << ' ' << 3 << (i == N-2 ? '\n' : ' ');
            continue;
        }
        cout << 2 << ' ' << 2 << ' ';
        for(int i = 2; i<N; i+=2) cout << 1 << ' ' << 3 << (i == N-2 ? '\n' : ' ');
    }
}


