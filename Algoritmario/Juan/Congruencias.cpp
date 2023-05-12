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

rp solve(ll c1, ll c2, ll b){
    rp ans = mygcd(c1,c2);
    if(b%ans.first != 0) return {-1,{-1,-1}};
    ll bd = b/ans.first;
    ll c2p = c2/ans.first;

    ans.second.first *= bd;
    ans.second.first = (ans.second.first%(c2p)+c2p)%c2p;

    ans.second.second = (b-ans.second.first*c1)/c2;
    return ans;
}

// Falta checar que el lcm no cause overflow
pll sistema(vll& c, vll& b){
    pll ans(b[0], c[0]);
    for(size_t i=1; i<c.size(); i++){
        ll pc = ans.second;
        ll pb = ans.first;
        rp sol = solve(pc, c[i],b[i]-pb);
        if(sol.first == -1) return {-1,-1};

        ans.second = pc*c[i]/sol.first;
        ans.first += pc*sol.second.first;
        ans.first %= ans.second;
    }
    return ans;
}
