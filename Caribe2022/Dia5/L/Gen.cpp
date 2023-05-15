#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;


int main(){
    ll N,M; 
    const long long maxk=39;
    srand(arc4random());
    N=10000;
    M=45;
    cout << N << ' ' << M << '\n';
    for(int i=0; i<N; i++){
        unordered_set<ll> st;
        ll k=rand()%maxk+1;
        k=min(M,k);
        while((ll)st.size() < k) st.insert(rand()%(M)+1);
        for(int i=0; i<k; i++) ;
        cout << st.size() << ' ';
        for(ll x: st) cout << x << ' ';
        cout << endl;
    }
}


