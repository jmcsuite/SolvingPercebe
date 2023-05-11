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
    rp ans={prev.first, {prev.second.second-prev.second.first*(b/a),
        prev.second.first}};
    return ans;
}

rp solve(ll c1, ll c2, ll b){
    rp ans = gcd(c1,c2);
    if(b%ans.first != 0) return {-1,{-1,-1}};
    ll bd = b/ans.first;
    ans.second.first*=bd;
    ans.second.second*=bd;
    return ans;
}

pll sistema(vll& c, vll& b){
    pll ans(b[0], c[0]);
    for(size_t i=1; i<c.size(); i++){
        ll pc=ans.second;
        ll pb=ans.first;
        rp sol = solve(pc,c[i],b[i]-pb);
        if(sol.first == -1) return {-1,-1};
        ans.first += pc*sol.second.first;
        ans.second = pc*c[i]/sol.first;
    }
    return ans;
}
