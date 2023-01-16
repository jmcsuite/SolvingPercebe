#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string S; ll N; cin>>S; N=S.size();
    vll vl(N+1);
    vll ans(N+1);
    vl[0] = 0;
    ll guess = 1;
    for(int i = 1; i < N; i++){
        while(guess != 0 && S[i] != S[guess-1]) guess = min(guess-1,vl[max(ll(0),guess-2)]+1);
        vl[i] = guess;
        guess++;
    }
    for(int i = 0 ; i < N; i++) ans[i]++;

    for(int i = N-1; i >= 0; i--){
        if(vl[i] != 0) ans[vl[i]-1] += ans[i];
    }

    vll indexes;
    ll index = N-1;
    while(index >= 0){
        indexes.push_back(index);
        index = vl[index];
        index--;
    }
    sort(indexes.begin(),indexes.end());
    cout << indexes.size() << '\n';
    for(size_t i = 0; i < indexes.size(); i++){
        cout << indexes[i]+1 << ' ' << ans[indexes[i]] << '\n';
    }
}

