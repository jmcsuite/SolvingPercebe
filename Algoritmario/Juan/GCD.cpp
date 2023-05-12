using rp = pair<ll,pll>;

rp mygcd(ll a, ll b){
    if(a==0) return {b,{0,1}};
    if(b==0) return {a,{1,0}};
    rp prev=mygcd(b%a,a);

    ll bd = b/prev.first;
    ll ax=prev.second.second-prev.second.first*(b/a);
    ax = (ax%bd+ bd)%bd;
    ll bx=(prev.first-a*ax)/b;
    
    rp ans={prev.first, {ax,
        bx}};
    return ans;
}
// sea c = max(a,b), la solucion |x| <= c

// Soluciones de ax + by = 0.
// d = gcd(a,b); -> x=(b/d)*t, y=-1*(a/d)*t;
