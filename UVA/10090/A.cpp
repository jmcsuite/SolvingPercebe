#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

using rp = pair<ll,pll>;
rp gcd(ll a, ll b){
    if(a==0) return {b,{0,1}};
    if(b==0) return {a,{1,0}};
    rp prev=gcd(b%a,a);
    rp ans={prev.first,{prev.second.second-prev.second.first*(b/a), prev.second.first}};
    return ans;
}

int main(){
    ll N;
    while(cin>>N,N){
        ll c1, n1; cin>>c1>>n1;
        ll c2, n2; cin>>c2>>n2;
        bool sw=false;
        if(n1*c2 < n2*c1){
            swap(n1,n2);
            swap(c1,c2);
            sw=true;
        }

        rp ans=gcd(n1, n2);
        if(N%ans.first != 0){
            cout << "failed\n";
            continue;
        }

        /*cout << n1 << ' ' << n2 << endl;
        cout << ans.first << ' ' << ans.second.first << ' ' << ans.second.second << endl;
        assert((n1*ans.second.first+n2*ans.second.second) == ans.first); */
        ll d=ans.first;
        ans.second.first*= (N/d);
        ans.second.second*= (N/d);

        ll n1Prime=n1/d;
        ll t=ans.second.second/(n1Prime);
        //cout << "DEBUG: " << n1 << ' ' << ans.second.second << ' ' << n1Prime << ' ' << t << endl;
        if(ans.second.second < 0 && ans.second.second%n1Prime != 0) t--;

        ll a1=ans.second.first+n2*t/d;
        ll a2=ans.second.second-n1*t/d;
        if(a1 < 0 || a2 < 0){
            cout << "failed\n";
            continue;
        }
        if(sw) swap(a1,a2);
        cout << a1 << ' ' << a2 << endl;
    }
}

            
    
