// Lazy Segment Tree.
// 1.- This segment tree doesn't know the range of the interval
// 2.- The order opperations must'nt matter (assigment doesn't work)
const int maxn;
struct segmentTree{
    struct st[2*maxn];
    ll n;
    ll h;
    struct d[2*maxn];
    struct merge(struct& a, struct& b){
        // define merge function
        // return struct c;
    }
    struct ifPropagated(ll idx){
       // return st[idx] + operationOf(d[idx]);
    }
    void build(ll sz){
        n = sz;
        // calcularel numero de bits de n;
        h = 64-__builtin_clzll(n);
        for(int i=0; i<n; i++){
            //st[i+n] = val; assignar los valores iniciales
        }
        for(int i=n-1; i>0; i--){
            st[i]=merge(st[i*2],st[i*2+1]);
        }
    }

    void apply(ll i, ll x){
        //apply update of value X, to segment i;
        //remember to update d[i] aka, values not propagated to children
    }

    void bi(ll x){
        //update all parents of x;
        for(x/=2; x; x/=2){
            st[x] = merge(st[x*2], st[x*2+1]);
            // IMPORTANTE. El flag d[x] puede no haberse propagado;
            // Cual seria el valor de st[x], si d[x] se hubiera propagado?
            // Ejemplo si nuestra operacion es la suma, st[x] += range*d[x]
            st[x] = ifPropagated(x);
        }
    }

    // [l,r); 0 based indexed
    void update(ll l, ll r, ll x){
        ll l0 = l+n;
        ll r0 = r+n-1;
        for(l+=n,r+=n; l<r; l/=2, r/=2){
            if(l%2) apply(l++, x);
            if(r%2) apply(--r, x);
        }
        bi(l0);
        bi(r0);
    }

    // propagate lazy before doing queries
    void push(ll x){
        for(int s=h; s>0; s--){
            int i = x>>s;
            if(d[i] != 0){
                apply(i*2, d[i]);
                apply(i*2+1, d[i]);
            }
            d[i] = 0;
        }
    }

    // Query from [l,r), 0-indexed;
    struct query(ll l, ll r){
        push(l+n);
        push(r+n-1);
        bitset<maxb> ansl;
        bitset<maxb> ansr;
        for(l+=n,r+=n; l<r; l/=2,r/=2){
            if(l%2) ansl= merge(ansl, st[l++]);
            if(r%2) ansr = merge(st[--r], ansr);
        }
        return merge(ansl,ansr);
    }
};
        

        
