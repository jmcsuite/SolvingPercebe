#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using vll = vector<ll>;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll seed = arc4random();
    srand(seed);
    ll T = rand();
    T%=2; T++;
    cout << T << '\n';
    for(int i=0; i<T; i++){
        ll N = (ll(rand())%5)+1;
        cout << N << '\n';
        ll rootImg = (ll(rand())%N)+1;
        vector<vector<ll>> level(N);
        vector<ll> myLevel(N+1);

        level[0].push_back(rootImg);
        myLevel[rootImg]=0;

        ll minLevel=1;
        ll levels=1;

        for(int i=1; i<=N; i++){
            if(i == rootImg) continue;
            ll my = rand()%levels+minLevel;
            if(my == levels) levels++;
            myLevel[i] = my;
            level[my].push_back(i);
        }

        vll parents(N+1);
        for(int i=1; i<=N; i++){
            if(i == rootImg) continue;
            ll my = myLevel[i];
            ll up = level[my-1].size();
            ll idx = rand()%up; 
            parents[i] = level[my-1][idx];
        }

        for(int i=1; i<=N; i++){
            if(i == rootImg) continue;
            ll how=(ll(rand()%2));
            if(how){
                cout << parents[i] << ' ' << i << '\n';
            }else{
                cout << i << ' ' << parents[i] << '\n';
            }
        }

        for(int i=1; i<=N; i++){
            ll num = (ll(rand()%10) + 1);
            cout << num << ' ';
        }
        cout << '\n';

        ll Q = (rand()%5+1);
        cout << Q << '\n';
        for(int i=0; i<Q; i++){
            ll a=rand()%N+1;
            ll b=rand()%N+1;
            cout << a << ' ' << b << '\n';
        }
        cout << flush;
    }
}
