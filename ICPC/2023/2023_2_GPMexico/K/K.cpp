#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const ll maxn = 1000;
ll arr[maxn][maxn];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N, K; cin>>N>>K;
    K--;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin>>arr[i][j];
    }

    ll ans = 0;
    for(int i=0; i<N-K; i++){
        for(int j=0; j<N-K; j++){
            if(arr[i][j] != arr[i+K][j]) continue;
            if(arr[i][j] != arr[i+K][j+K]) continue;
            if(arr[i][j] != arr[i][j+K]) continue;
            ans++;
        }
    }
    cout << ans << '\n';
}
