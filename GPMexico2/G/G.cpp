#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;

    vll dis(N-1);
    vll times(N);
    for(int i =0; i<N-1; i++) cin >> dis[i];
    for(int i=0; i<N; i++) cin>>times[i];


    vll aX(N);
    vll bX(N);
    vll aY(N);
    vll bY(N);

    ll start = 0;
    ll iDis = N-2;
    ll iTimes = N-1;

    while(iTimes >= 0){
        aX[iTimes] = start;
        bX[iTimes] = start + times[iTimes];
        start += times[iTimes];
        if(iDis >= 0) start += dis[iDis];
        iTimes--;
        iDis--;
    }

    start = 0;
    iDis = 0;
    iTimes = 0;
    while(iTimes < N){
        aY[iTimes] = start;
        bY[iTimes] = start + times[iTimes];
        start += times[iTimes];
        if(iDis < N-1) start += dis[iDis];
        iDis++;
        iTimes++;
    }
    ll ans = 0;
    for(int i =0; i<N; i++){
        ans += max(ll(0), min(bY[i], bX[i]) - max(aY[i], aX[i]));
    }
    cout << ans << '\n';
}