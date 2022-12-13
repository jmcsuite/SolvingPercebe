#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    bool se = true;
    for(int i = 0; i < 8; i++){
        ll a; cin>>a;
        if(a==9) se=false;
    }
    cout << (se ? 'S' : 'F') << '\n';
}