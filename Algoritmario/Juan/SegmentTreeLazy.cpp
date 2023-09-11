struct segmentTree{
    struct str{
        ll hash;
        ll sz;
        str() : hash(0), sz(0) {}
        str(ll h, ll s) : hash(h), sz(s) {}
    };

    str st[2*maxn];
    ll n;
    ll h;
    ll d[2*maxn];
    str merge(str& a, str& b){
        // combine a,b
    }

    str ifPropagated(ll idx){
        if(d[idx] == 0) return st[idx];
        // value of st[idx] if you had propagated d[idx]
        // If propagated is alwas asked after st[idx] = merge(st[idx*2], st[idx*2 + 1]);
    }

    void apply(ll i, ll x){
        // apply lazy x. Remember to update d[i], flag not propagated to children
        // apply directly to st[i], that is the value used in queries
    }

    void build(vll& vl, ll sz){
        n=sz;
        h=64-__builtin_clzll(n);
        for(int i=0; i<n; i++) st[i+n] = {};
        for(int i=n-1; i>0; i--) st[i]=merge(st[i*2],st[i*2+1]);
    }

    void bi(ll x){
        for(x/=2; x; x/=2){
            st[x] = merge(st[x*2],st[x*2+1]);
            st[x]=ifPropagated(x);
        }
    }

    void push(ll x){
        for(int s=h; s>0; s--){
            int i=x>>s;
            if(d[i] != 0){
                apply(i*2, d[i]);
                apply(i*2+1,d[i]);
            }
            d[i]=0;
        }
    }

    //[l,r) 0-indexed
    void update(ll l, ll r, ll x){
        ll l0 = l+n;
        ll r0 = r+n-1;
        push(l0);
        push(r0);
        
        for(l+=n,r+=n; l<r; l/=2,r/=2){
            if(l%2) apply(l++,x);
            if(r%2) apply(--r,x);
        }
        bi(l0);
        bi(r0);
    }

    //[l,r) 0-indexed
    str query(ll l, ll r){
        push(l+n);
        push(r+n-1);
        str ansl(0,0);
        str ansr(0,0);
        for(l+=n,r+=n; l<r; l/=2,r/=2){
            if(l%2) ansl = merge(ansl,st[l++]);
            if(r%2) ansr = merge(st[--r],ansr);
        }
        return merge(ansl,ansr);
    }
};
