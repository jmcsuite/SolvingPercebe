#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    string a; cin >> a;
    a.push_back('b');
    N++;
    ll ans = 0;
    ll cc = 0;
    for(int i = 0; i < N; i++){
        if(a[i] == 'b'){
            if(cc > 1) ans+=cc;
            cc = 0;
        }
        else{
            cc++;
        }
    }
    cout << ans << endl;
}