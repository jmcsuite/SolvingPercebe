#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    if(N == 1){
        cout << "1 1" << endl;
        cout << "0 0 0 1" << endl;
        return 0;
    }
    string s;
    cout << "0 1" << endl;
    cin >> s;
    ll inc = 1e9/2;
    ll L = 0;
    for(int i=1; i<N; i++){
        cout << L+inc << ' ' << 1 << endl;
        string nex; cin>>nex;
        if(nex == s) L+=inc;
        if(i!=N-1) inc/=2;
    }
    cout << L << ' ' << 2 << ' ' << L+inc << ' ' << 0 << endl;
}
