#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while(T--){
        
        ll maxi = -1;
        ll mini = 1e6;
        ll N; cin >> N;
        vll vl(N);
        for(int i = 0; i < N; i++) cin >> vl[i];
        for(int i = 0; i < N; i++) maxi = max(maxi,vl[i]);
        for(int i = 0; i < N; i++) mini = min(mini, vl[i]);
        ll cm = 0;
        ll cmini = 0;
        for(int i = 0; i < N; i++){
            if(maxi == vl[i]) cm++;
            if(mini == vl[i]) cmini++;
        }
        if(maxi == mini){
            cout << N*(N-1) << '\n';
            continue;
        }
        cout << cm*cmini*2 << '\n';
    }
}
