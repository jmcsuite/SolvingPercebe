/*
ID: jmcsuit1 
LANG: C++14
TASK: ride 
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("ride.in", "r", stdin);
    freopen("ride.out", "w", stdout);
    string A,B; cin>>A>>B;
    ll a,b; a=1; b=1;
    for(char c: A){
        a = (a* ((int)c-'A'+1));
        a%=47;
    }
    for(char c: B){
        b = (b* ((int)c-'A'+1));
        b%=47;
    }
    if(a == b) cout << "GO\n";
    else cout << "STAY\n";
    return 0;
}

