using rp = pair<ll,pll>;
rp gcd(ll a, ll b){
    if(a==0) return {b,{0,1}};
    if(b==0) return {a,{1,0}};
    rp prev=gcd(b%a,a);
    rp ans={prev.first,{prev.second.second-prev.second.first*(b/a), prev.second.first}};
    return ans;
}

// Soluciones de ax + by = 0.
// d = gcd(a,b); -> x=(b/d)*t, y=-1*(a/d)*t;
