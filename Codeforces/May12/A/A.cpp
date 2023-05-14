#include<bits/stdc++.h>
using namespace std;
using ll = long long;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        string s; cin>>s;
        ll N=s.size();
        bool se=true;
        for(int i=1; i<(N/2); i++){
            if(s[i]!=s[i-1]) se=false;
        }
        if(se) cout << "NO\n";
        else cout << "YES\n";
    }
}
