#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

ll N,K,T;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>K>>T;
    vll vl(N);
    for(int i=0; i<N; i++) cin>>vl[i];
    ll ans = 0; 
    ll dis = 0;
    for(int i=N-2; i>=0; i--){
        dis += vl[i+1]-vl[i];
        ans+=dis;
    }

    ll orgAns = 0;
    orgAns = ans;
    ll ansI = 0; 
    ll ansJ = 0;
    for(int i=0; i<N; i++){
        ll ini = i;
        ll inc = N/2+1;
        ll maxi = vl[i] + K;
        while(inc){
            if(ini + inc < N && vl[ini+inc]<=maxi) ini+=inc;
            else inc/=2;
        }
        ll tramo = vl[ini]-vl[i];
        if(tramo > T){
            ll guess = orgAns - ((tramo-T)*(i+1));
            if(guess < ans){
                ans = guess;
                ansI = i;
                ansJ = ini;
            }
        }
    }
    if(ans == orgAns){
        cout << -1 << endl;
        return 0;
    }
    cout << ansI+1 << ' ' << ansJ+1 << ' ' << ans << endl;
}


