#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;
 
 
map<ll,double> dp;
map<ll,bool> vis;
ll N,M;
ll transform(vll& A, vll& B){
    ll val=0;
    for(int i=0; i<N; i++){
        val*=7;
        val+=A[i];
    }
    for(int i=0; i<M; i++){
        val*=7;
        val+=B[i];
    }
    return val;
}
 
void getOr(vll& A, vll& B, ll x){
    A.resize(N);
    B.resize(M);
    for(int i=M-1; i>=0; i--){
        B[i] = x%7;
        x/=7;
    }
    for(int i=N-1; i>=0; i--){
        A[i] = x%7;
        x/=7;
    }
    return;
}
 
ll D;
 
 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>M>>D;
    queue<pll> q;
    vll A(N);
    vll B(M);
    for(int i=0; i<N; i++) cin>>A[i];
    for(int j=0; j<M; j++) cin>>B[j];
    ll maxiSum = 0;
    for(int i=0; i<N; i++) maxiSum+=A[i];
    for(int i=0; i<M; i++) maxiSum+=B[i];
    D = min(maxiSum, D);

    sort(A.rbegin(), A.rend());
    sort(B.rbegin(), B.rend());
 
    ll allCero=1;
    ll pad = 1;
    for(int i=0; i<N; i++) allCero*=7;
    for(int i=0; i<M; i++) pad*=7;
    vll tmpA,tmpB;
    for(int i=0; i<allCero; i++){
        getOr(tmpA, tmpB,i*pad);
        bool se = true;
        ll ppCount=0;
        for(int j=0; j<N; j++){ // Primer Bug
            if(tmpA[j] > A[j]) se = false;
            if(j >= 1 && tmpA[j] > tmpA[j-1]) se = false;
            ppCount += A[j] - tmpA[j];
        }
        for(int j=0; j<M; j++){
            ppCount+=B[j];
        }
        if(!se) continue;
        if(ppCount != D) continue;
        //cout << tmpA[0] << ' ' << tmpA[1] << endl;
        //cout << i*pad << endl;
        q.push({i*pad, 0});
        vis[i*pad]=1;
        dp[i*pad]=1;
    }
 
    //cout << D << endl;
 
    while(!q.empty()){
        //cout << "BBBB" << ' ' << B[0] << endl;
        pll p = q.front();
        q.pop();
        if(p.second >= D) continue;
        ll x = p.first;
        getOr(tmpA, tmpB, x);
        bool aaa=true;
        for(int i=0; i<M; i++) if(tmpB[i] != 0) aaa=false;
        if(aaa) dp[x] = 1;
        /*
        cout << "Case " << p.second << " DP: " << dp[x] << endl;
        for(int i=0; i<N; i++){ cout << tmpA[i] << ' '; }
        for(int i=0; i<M; i++){ cout << tmpB[i] << ' '; }
        cout << endl;
        cout << x << endl;
        cout << endl;*/
        ll alive=0;
        for(int i=0; i<N; i++){
            if(tmpA[i] != 0) alive++;
        }
        for(int i=0; i<M; i++){
            if(tmpB[i] != 0) alive++;
        }
        ll nAlive = alive;
        bool invalid = true;
        for(int i=0; i<N; i++){
            invalid = false;
            ll nNext = x;
            if(tmpA[i] == 0) nAlive = alive+1;
            else nAlive = alive;
            if(i != 0 && tmpA[i] == tmpA[i-1]) continue; 
            else{
                tmpA[i]++;
                if(tmpA[i] > A[i]) invalid=true;
                else invalid=false;
                nNext = transform(tmpA, tmpB);
                tmpA[i]--;
            }
            ll countArriba=1;
            for(int j=0; j<N; j++) if(tmpA[i] + 1 == tmpA[j]) countArriba++;
 
            if(!invalid){
                dp[nNext] += dp[x]*(double(countArriba)/double(nAlive));
                if(!vis[nNext]){
                    q.push({nNext, p.second+1});
                    vis[nNext]=1;
                }
            }
        }
 
        invalid = true;
        for(int i=0; i<M; i++){
            invalid = false;
            ll nNext = x;
            ll countArriba=1;
            if(tmpB[i] == 0) nAlive = alive+1;
            else nAlive = alive;
            if(i != 0 && tmpB[i] == tmpB[i-1]) continue;
            else{
                tmpB[i]++;
                if(tmpB[i] > B[i]) invalid=true;
                else invalid=false;
                nNext = transform(tmpA, tmpB);
                tmpB[i]--;
            }
            for(int j=0; j<M; j++) if(tmpB[i]+1 == tmpB[j]) countArriba++;
 
 
            /*if(tmpA[0] == 2 && tmpB[0] == 1){
                cout << "VISITA PAPAL NOT" << endl;
                cout << i << ' ' << tmpB[i] << ' ' << B[i] << endl;
                cout << invalid << ' ' << vis[nNext] << endl;
                cout << countArriba << endl;
                cout << nAlive << ' ' << alive;
            }*/
            if(!invalid){
                dp[nNext] += dp[x]*(double(countArriba)/double(nAlive));
                if(!vis[nNext]){
                    q.push({nNext, p.second+1});
                    vis[nNext]=1;
                }
            }
        }
    }
    ll px = transform(A,B);
    cout << fixed << setprecision(6) << dp[px] << '\n';
}

