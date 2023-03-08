#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    vll acum(N);
    vector<pair<ll, pll>> vpll(N);
    for(int i=0; i<N; i++){
        ll d, dead; cin>>d>>dead;
        vpll[i] = {dead,{d,i+1}};
    }
    sort(vpll.begin(), vpll.end());
    for(int i=0; i<N; i++) vpll[i].first-=vpll[i].second.first;
    vll difs(N);
    ll ss = 0;
    for(int i=0; i<N; i++){
        difs[i] = vpll[i].first-ss;
        if(difs[i] < 0){
            cout << "*" << endl;
            return 0;
        }
        ss+=vpll[i].second.first;
    }
    ll orgSum=0;
    vll ans;
    for(int k=0; k<N; k++){
        ll mini = 1e15;
        ll sum = orgSum;
        ll anis = 1e15;
        ll indexAnis = -1;
        for(int i=0; i<N; i++){
            if(acum[i] != 0){
                sum-=acum[i];
                continue;
            }
            if(vpll[i].second.first <=mini && anis > vpll[i].second.second){
                anis = vpll[i].second.second;
                indexAnis = i;
            }
            mini = min(mini, difs[i]-sum);
        }
        ans.push_back(anis);
        orgSum+=vpll[indexAnis].second.first;
        acum[indexAnis]+=vpll[indexAnis].second.first;
    }
    for(int i=0; i<N; i++) cout << ans[i] << (i == N-1 ? "\n" : " ");
}

