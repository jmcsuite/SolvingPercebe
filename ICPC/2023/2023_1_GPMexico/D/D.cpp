#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N,Q; cin>>N>>Q;
    vll vl(N);
    for(int i=0; i<N; i++) cin>>vl[i];
    sort(vl.begin(),vl.end());

    auto last = [&](ll k){
        ll ans = -1;
        ll inc = vl.size()/2 + 1;
        while(inc){
            if(ans+inc < (int)vl.size() && vl[ans+inc] <= k) ans+=inc;
            else inc/=2;
        }
        return ans;
    };

    auto first = [&](ll k){
        ll ans = vl.size();
        ll inc = vl.size()/2+1;
        while(inc){
            if(ans-inc >= 0 && vl[ans-inc] >= k) ans-=inc;
            else inc/=2;
        }
        return ans;
    };

    while(Q--){
        ll q,a,b; cin>>q>>a;
        if(q == 2){
            cin >> b;
            cout << last(b)-first(a)+1 << '\n';
            //cout << first(a) << ' ' << last(b) << endl;
            continue;
        }
        ll k=a;
        
        ll f = first(k);
        if(f != (int)vl.size() && vl[f] == k) continue;
        if(f == (int)vl.size()){
            vl.push_back(k);
            continue;
        }
        vl[f]=k;
    }
}





