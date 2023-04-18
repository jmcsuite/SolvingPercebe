#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=100000;
const int maxk=20;
const int maxm = (1 << maxk);


ll dp[maxm];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,K; cin>>N>>K;

    queue<ll> q;
    for(int i=0; i<N; i++){
        ll num=0;
        for(int j=0; j<K; j++){
            num*=2;
            char c; cin>>c;
            if(c == '1') num++;
        }
        q.push(num);
        dp[num]=1;
    }

    ll ans = 0;
    while(!q.empty()){
        ll x = q.front(); q.pop();
        ans = x;
        dp[x]=1;
        for(int i=0; i<K; i++){
            ll nx = x^(1<<i);
            if(dp[nx]) continue;
            dp[nx] = 1;
            q.push(nx);
        }
    }
    for(int i=K-1; i>=0; i--){
        if((ans& (1<<i)) == 0) cout << '0';
        else cout << '1';
    }
    cout << '\n';
}



