#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=100000;

ll ans[2][maxn];

void solve(ll N){
    ll ini=2*N-1;
    for(int i=0; i<N; i+=2){
        ans[0][i] = ini;
        ini-=2;
    }
    ini = 2*N;
    for(int i=N-1; i>=0; i-=2){
        ans[1][i] = ini;
        ini-=2;
    }
    ini = 1;
    for(int i=1; i<N; i+=2){
        ans[0][i] = ini;
        ini+=2;
    }
    ini = 2;
    for(int i=N-2; i>=0; i-=2){
        ans[1][i] = ini;
        ini+=2;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N; cin>>N;
        solve(N);
        for(int i=0; i<N; i++) cout << ans[0][i] << (i == N-1 ? '\n' : ' ');
        for(int i=0; i<N; i++) cout << ans[1][i] << (i == N-1 ? '\n' : ' ');
    }
}

