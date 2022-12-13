#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N; cin >> N;
    ll K = N/4;
    if(N%4 <= 1) cout << K * K;
    else cout << K * (K + 1);
    cout << endl; 
}