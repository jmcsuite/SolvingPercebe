struct segmentTree{
    struct str{
        ll first;
        ll second;
        str() : first(0), second(0) {}
        str(ll a, ll b) : first(a), second(b) {}
    };

    str func(str a, str b){ 
        //merge function
    }

    str st[2*maxn];
    ll n;

    void build(vll& vl, int sizn){
        n = sizn;
        for(int i=0;i<n;i++) st[i+n] = {vl[i],i};
        for(int i=n-1;i>0;i--) st[i] = func(st[i*2],st[i*2+1]);
    }

    // 0-indexed
    // Value is replaced
    void update(int pos, str x){
        for(pos+=n,st[pos]=x,pos/=2; pos; pos/=2){
            st[pos] = func(st[pos*2],st[pos*2+1]);
        }
    }

    //[L,R) 0-indexed
    str query(int l, int r){
        str ansl={0,0};
        str ansr={0,0};
        for(l+=n,r+=n;l<r;l/=2,r/=2){
            if(l%2) ansl=func(ansl,st[l++]);
            if(r%2) ansr=func(st[--r],ansr);
        }
        return func(ansl,ansr);
    }
};
