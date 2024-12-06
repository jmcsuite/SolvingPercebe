#include<bits/stdc++.h>
using namespace std;
using ll = long long;

map<string, int> mp;

int main(){
    ll N; cin>>N;
    for(int i=0; i<N; i++){
        ll M; cin>>M;
        string name;
        for(int j=0; j<M; j++){
            string temp; cin>>temp; 
            name.push_back(temp[0]);
        }
        mp[name]++;
    }

    ll ans=0;
    for(auto& p : mp){
        //cout << p.first << '\n';
        if(p.second == 1) ans++;
    }
    cout << ans << '\n';
}
