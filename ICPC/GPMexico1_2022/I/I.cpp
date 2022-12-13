#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll a = 0;
    ll N;
    cin >> N;
    ll M = N;
    for(ll i = 0; i < 8; i++){
        ll b = M%10;
        if(b != 0 && N % b == 0) a++;
        M /= 10;
    }
    cout << a << '\n';
}