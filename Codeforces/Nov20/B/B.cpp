#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<long long>;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T;
    cin >> T;
    while(T--){
        ll N;
        cin >> N;
        vll vl(N);
        for(int i =0; i<N;i++){
            cin >> vl[i];
        }
        if(N < 4) {
            cout << N << '\n';
            continue;
        }
        bool se = true;
        for(int i = 2; i < N; i++) if(vl[i] != vl[i-2]) se = false;
        cout << (se ? (N/2)+1 : N) << '\n';
    }
}