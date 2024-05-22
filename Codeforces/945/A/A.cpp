#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while (T--) {
        ll a,b,c;
        cin >> a >> b >> c;
        if ((a+b+c) % 2) {
            cout << -1 << '\n';
            continue;
        }
        
        if((a+b) >= c) {
            cout << ((a+b+c)/2) << '\n';
            continue;
        }

        cout << (a+b) << '\n';
    }
}
