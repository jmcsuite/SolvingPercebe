#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin>>N>>M;
    if(M%2){
        N--; 
        N%=(M+1);
        if(N == M) cout << "Free snacks!" <<endl;
        else cout <<   "Pay the bill" << endl;
    }
    else{
        N--;
        N%=(M+2);
        if(N == M || N == (M+1)) cout << "Free snacks!" << endl;
        else cout << "Pay the bill" << endl;
    }
}
