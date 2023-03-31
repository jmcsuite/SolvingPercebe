#include<bits/stdc++.h>
using namespace std;

const int maxn=300;
ll vl[maxn];

ll DP[maxn][19][19][3];

ll func(ll idx, ll mN, ll L,ll R,ll flag){



int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,A,B;
    cin>>N>>A>>B;
    for(int i=0; i<N; i++) cin>>vl[i];
