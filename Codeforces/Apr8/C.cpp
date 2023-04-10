#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N,M; cin>>N>>M;
        ll x,y; 
        x=1; y=1;
        cout << "? 1 1" << endl;
        ll dif=0; cin>>dif;
        x+=dif; y+=dif;
        x = min(x,N);
        y = min(y,M);

        ll xx = x;
        ll yy = y;
        cout << "? " << x << ' ' << y << endl;
        cin>>dif;
        ll d2 = dif;
        y-=dif;
        y = min(y,M);
        cout << "? " << x << ' ' << y << endl;
        cin>>dif;
        if(dif != 0) {
           x = xx-d2;
           y = yy;
        }
        cout << "! " << x << ' ' << y << endl;
    }
}
