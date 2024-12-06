#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; string s; cin>>N>>s;
    char b = s[s.size()-1];
    string s2 = s.substr(0,s.size()-1);
    stringstream ss(s2);
    ll M; ss >> M;
    if(b == 'T') M = M*1024*1024;
    if(b == 'G') M = M*1024;
    vll vl(N);
    for(int i=0; i<N; i++) cin>>vl[i];
    for(int i=1; i<N; i++) vl[i]+=vl[i-1];

    auto sum = [&](ll i, ll sz){
        ll j = i+sz-1;
        j = min(N-1,j);
        ll ans = vl[j];
        if(i) ans-=vl[i-1];
        return ans;
    };

    auto can = [&](ll sz){
        for(int i=0; i<N; i++){
            ll pp = sum(i,sz);
            if(pp > M) return false;
        }
        return true;
    };

    ll ini = 0; 
    ll step = max(N/2, ll(1));
    while(step){
        if(ini + step <= N && can(ini+step)) ini+=step;
        else step/=2;
    }
    ll a1 = ini;
    if(ini == N) {
        cout << ini << ' ' << -1 << '\n';
        return 0;
    }
    cout << ini << ' ';
    for(int i=0; i<N; i++){
        ll pp = sum(i,a1+1);
        if(pp > M) {
            cout << i+1 << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
}

