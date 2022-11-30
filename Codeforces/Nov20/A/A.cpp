#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<long long>;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll Q; cin >> Q;
    while(Q--){
        ll a,b,c; cin >> a >> b >> c;
        if(b + c == 2*a){
            cout << "Yes\n";
            continue;
        }
        if(b+c+2<=a){
            cout << "Yes\n";
            continue;
        }
        cout << "No\n";
    }
}
