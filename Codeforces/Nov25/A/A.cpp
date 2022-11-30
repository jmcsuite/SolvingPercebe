#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll Q; cin>>Q;
    while(Q--){
        string a,b;
        cin>>a;
        ll N = a.size();
        b.resize(2*N);
        for(int i = 0; i < N; i++){
            b[i] = a[i];
            b[2*N-i- 1] = a[i];
        }
        cout << b << '\n';
    }
}