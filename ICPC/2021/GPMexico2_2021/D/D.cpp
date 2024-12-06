#include<bits/stdc++.h>
using namespace std;
using ll = long long;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll C,R,S; cin>>C>>R>>S;
        ll mC = C%S;
        ll mR = R%S;
        ll a1 = C/S;
        if(mC+mR > S) a1++;
        if(mR == 0 && mC != 0) a1++;
        ll C2 = C-(S-1)*R;
        ll a2 = C2/S;
        if(C2 > 0 && C2%S != 0) a2++;
        a2 = max(ll(0),a2);
        cout << a1 << ' ' << a2 << '\n';
    }
}
