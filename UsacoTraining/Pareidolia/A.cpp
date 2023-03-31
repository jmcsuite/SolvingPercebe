#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=2e5;
const int maxc=6;

char name[maxc]={'b','e','s','s','i','e'};
ll cost[maxn];

pll dp[maxn][maxc];
ll N;
string s;

pll sum(pll a, pll b){
    pll c(a.first+b.first,a.second+b.second);
    return c;
}

pll best(pll a, pll b){
    if(a.first == b.first){
        if(a.second < b.second) return a;
        return b;
    }
    if(a.first > b.first) return a;
    return b;
}

pll func(ll x, ll idx){
    if(x == N) return {0,0};
    if(dp[x][idx].first != -1) return dp[x][idx];
    if(s[x] != name[idx]){
        pll a1(0,cost[x]); //quitarlo
        pll a2(0,0); //dejarlo
        pll b1 = func(x+1,idx);
        pll b2 = func(x+1,0);
        a1 = sum(a1, b1);
        a2 = sum(a2, b2);
        pll ans = best(a1,a2);
        dp[x][idx]=ans;
        return ans;
    }
    //if(x==6){
    //  cout << "One idx: " << idx << endl;
    //}
    pll a2(0,0);
    ll nx=idx+1;
    if(idx == maxc-1){
        nx=0;
        a2.first++;
    }
    pll b2 = func(x+1, nx);

    pll a1(0,cost[x]);
    pll b1 = func(x+1, idx);

    pll a3(0,0);
    pll b3 = func(x+1, 0);

    a1 = sum(a1, b1);
    a2 = sum(a2, b2);
    a3 = sum(a3, b3);

    a1 = best(a1,a2);
    a1 = best(a3, a1);
    dp[x][idx]=a1;
    return a1;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s;
    N = s.size();
    for(int i=0; i<N; i++) cin>>cost[i];
    for(int i=0; i<N; i++){
        for(int j=0; j<maxc; j++){
            dp[i][j].first = -1;
        }
    }
    pll ans = func(0,0);
    cout << ans.first << '\n' << ans.second << '\n';
}


