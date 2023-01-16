#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

ll solve(ll lsb, vpll& input){
    ll N = input.size();
    vpll vl(N);
    for(int i=0; i<N; i++){
        vl[i].first=input[i].first;
        vl[i].second=input[i].second;
    }
    for(int i=0; i<N; i++){
        if(vl[i].second - vl[i].first + 1 >= lsb){
            vl[i].first = 0;
            vl[i].second = lsb-1;
        }else if(vl[i].first%lsb > vl[i].second%lsb){
            vl.push_back({0,vl[i].second%lsb});
            vl[i].first=vl[i].first%lsb;
            vl[i].second = lsb-1;
        }else{
            vl[i].first%=lsb;
            vl[i].second%=lsb;
        }
    }
    N = vl.size(); 
    vpll sum;
    for(int i=0; i<N; i++){
        sum.push_back({vl[i].first,0});
        sum.push_back({vl[i].second,1});
    }
    N = sum.size();
    ll ans = 0;
    ll cc = 0;
    sort(sum.begin(),sum.end());
    for(int i=0;i<N;i++){
        if(sum[i].second == 0) cc++;
        else cc--;
        ans = max(cc,ans);
    }
    return ans;
}

    
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N;cin>>N;
    vpll vl(N);
    for(int i=0; i<N; i++) cin>>vl[i].first>>vl[i].second;
    ll Q;cin>>Q;
    unordered_map<ll,ll> mp;
    for(int i=0; i<Q; i++){
        ll q; cin>>q;
        ll lsb = (q)&(-q);
        ll ans;
        if(mp[lsb] == 0){
            ans = solve(lsb,vl);
            mp[lsb] = ans;
        }else{
            ans = mp[lsb];
        }
        cout << ans << '\n';
    }
}
