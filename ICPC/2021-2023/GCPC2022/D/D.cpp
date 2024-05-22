#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll x=1;
    while(1){
        cout << "? " << x << endl;
        ll ans; cin>>ans;
        if(ans == 0){
            cout << "! " << x << endl;
            return 0;
        }else if(ans != x){
            cout << "! " << x-ans << endl;
            return 0;
        }
        x = x*2;
    }
}

