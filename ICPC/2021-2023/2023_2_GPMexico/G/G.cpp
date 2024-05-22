#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin>>N>>M;

    multiset<ll> s;
    multiset<ll> t;
    multiset<ll> p;

    map<ll,ll> in;
    map<ll,ll> self;
    map<ll,ll> out;

    for(int i=0; i<N; i++) s.insert(0);
    for(int i=0; i<N; i++) t.insert(0);
    for(int i=0; i<N; i++) p.insert(1);

    ll ans = 0;

    for(int i=0; i<M; i++){
        ll a,b; cin>>a>>b;
        a--; b--;


        s.erase(s.find(out[a]+self[a]));
        t.erase(t.find(in[b]+self[b]));
        p.erase(p.find(out[a]+self[a]*2+in[a]+1));


        if(a  != b ){
            p.erase(p.find(out[b]+self[b]*2+in[b]+1));
        }


       

        if(a == b){
            ans += in[a] + out[a] + self[a]*2 + 1;
            self[a]++; 
        }else{
            ans += in[a] + self[a] + out[b] + self[b];
            out[a]++;
            in[b]++;
        }

        s.insert(out[a]+self[a]);
        t.insert(in[b]+self[b]);
        p.insert(out[a]+self[a]*2+in[a]+1);
        if(a != b){
            p.insert(out[b]+self[b]*2+in[b]+1);
        }

        ll a1 = *s.rbegin() + *t.rbegin();
        a1 = max(a1, *p.rbegin());
        cout << ans << ' ' << a1 << '\n';
    }
}


