struct segmentTree{
    //Define Segment Tree container
    struct str{
        ll first;
        ll second;
        // important to define default initialization
        str(){
            first = 0;
             second = 0;
        }
        // useful to reduce code
        str(ll aa, ll bb){
             first= aa;
             second= bb;
        }
    };
    // Define Merge Function.
    // It can be associative or not.
    // aka it is fine that a + b != b + a
    str func(str a, str b){ 
        return (a.first < b.first ? a : b);
    }
    vector<str> st;
    ll n;
    // Recieves a 0-indexed array
    void build(vll& vl, int sizn){
        n = sizn;
        st.clear();
        st.resize(n*2);
        for(int i=0;i<n;i++){
            st[i+n].first = vl[i];
            st[i+n].second = i;
        }
        for(int i=n-1;i>0;i--){
            st[i]=func(st[i*2],st[i*2+1]);
        }
    }

    // Position is 0-indexed
    // Value is replaced
    void update(int pos, str x){
        pos+=n;
        st[pos] = x; 
        pos/=2;
        while(pos){
            st[pos] = func(st[pos*2],st[pos*2+1]);
            pos/=2;
        }
    }

    // Query in the interval from [L,R)
    // Def is the default, neutral value;
    str query(int l, int r, str def){
        str ansl=def;
        str ansr=def;
        for(l+=n,r+=n;l<r;l/=2,r/=2){
            if(l%2) ansl=func(ansl,st[l++]);
            if(r%2) ansr=func(st[--r],ansr);
        }
        return func(ansl,ansr);
    }
};
