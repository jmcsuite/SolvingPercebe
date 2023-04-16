#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn=1000000;
ll fib[maxn];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    fib[0] = 1;
    fib[1] = 1;
    for(int i=2; i <50; i++) fib[i] = fib[i-1] + 2*fib[i-2];
    cout << fixed << setprecision(7);
    ll N; cin>>N;
    if(N == 1){
        cout << "100 0" << endl;
        return 0;
    }
    if(N == 2){
        cout << "0 100" << endl;
        return 0;
    }
    if(N >= 53){
        cout << "33.3333333 66.6666666" << endl;
        return 0;
    }
    N-=3;
    ll a = N;
    double pp = double(fib[a]) / (double(fib[a] + fib[a+1]));
    pp*=100;
    cout << pp << ' ' << 100-pp << endl;
    return 0; 
}
