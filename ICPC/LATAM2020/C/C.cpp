#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    vll vl(3*N);
    vll v2(3*N);
    for(int i=0; i<N; i++) cin>>vl[i];
    
    ll sumTot=0; 
    for(int i=0; i<N; i++) sumTot+=vl[i];
    sumTot/=N;
    for(int i=0; i<N; i++) vl[i]-=sumTot;
    for(int i=0; i<N; i++) vl[i+N] = vl[i];
    for(int i=0; i<N; i++) vl[i+N+N] = vl[i];
    for(int i=0; i<3*N; i++) v2[i] = vl[3*N-i-1];
    ll ans = 0;
    for(int i=0; i<N; i++){
        if(vl[i] <= 0) continue;
        for(int j=i+N; j<i+2*N; j++){
            if(vl[j] > 0) vl[j] =0;
        }
        ll carry = 0;
        for(int j=i; j<i+2*N; j++){
            ans+=carry;
            if(vl[j] >= 0) carry+=vl[j];
            else{
                ll quito = min(carry,-1*vl[j]);
                vl[j]+=quito;
                carry-=quito;
                if(j <N) vl[j+N+N]+=quito;
                if(j <2* N) vl[j+N]+=quito;
            }
        }
        break;
    }
    for(int i=0; i<3*N; i++) vl[i]=v2[i];
    ll ans2 = 0;
    for(int i=0; i<N; i++){
        if(vl[i] <= 0) continue;
        for(int j=i+N; j<i+2*N; j++){
            if(vl[j] > 0) vl[j] =0;
        }
        ll carry = 0;
        for(int j=i; j<i+2*N; j++){
            ans2+=carry;
            if(vl[j] >= 0) carry+=vl[j];
            else{
                ll quito = min(carry,-1*vl[j]);
                vl[j]+=quito;
                carry-=quito;
                if(j <N) vl[j+N+N]+=quito;
                if(j <2* N) vl[j+N]+=quito;
            }
        }
        break;
    }
    ans=min(ans,ans2);
    cout << ans << endl;
}

