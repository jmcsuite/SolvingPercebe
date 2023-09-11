#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 2e5 + 1;

struct segmentTree{
    using str = long long;

    ll n;
    ll h;
    ll d[2*maxn];
    ll tam[2*maxn];
    str st[2*maxn];

    str merge(str a, str b){
        return a+b;
    }

    str ifPropagated(ll idx){
        return st[idx] + d[idx]*tam[idx];
    }

    void apply(ll i, ll x){
        d[i] += x;
        st[i] += tam[i]*x;
    }

    void build(vll &vl, ll sz){
        n=sz;
        h=64-__builtin_clzll(n);
        for(int i=0; i<n; i++) st[i+n] = 0;
        for(int i=n-1; i>0; i--) st[i]=merge(st[i*2], st[i*2+1]);

        for(int i=0; i<n; i++) tam[i+n] = 1;
        for(int i=n-1; i>0; i--) tam[i]=merge(tam[i*2], tam[i*2+1]);
    }

    void bi(ll x){
        for(x/=2; x; x/=2){
            st[x] = merge(st[x*2], st[x*2+1]);
            st[x] = ifPropagated(x);
        }
    }

    void push(ll x){
        for(int s=h; s>0; s--){
            int i=x>>s;
            if(d[i] != 0){
                apply(i*2, d[i]);
                apply(i*2+1, d[i]);
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
            if(r%2) apply(--r, x);
        }
        bi(l0);
        bi(r0);
    }

    //[l,r) 0-indexed
    str query(ll l, ll r){
        push(l+n);
        push(r+n-1);
        str ansl = 0;
        str ansr = 0;
        for(l+=n, r+=n; l<r; l/=2,r/=2){
            if(l%2) ansl = merge(ansl, st[l++]);
            if(r%2) ansr = merge(st[--r], ansr);
        }
        return merge(ansl, ansr);
    }
};

using pq = pair<pair<ll,ll>, ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, Q; cin >> N >> Q;
    vll vl(N); for(int i=0; i<N; i++) cin>>vl[i];
    
    vector<pq> vq(Q);
    for(int i=0; i<Q; i++){
        cin >> vq[i].first.first >> vq[i].first.second;
        vq[i].second = i;
        vq[i].first.first--;
    }

    sort(vq.rbegin(), vq.rend());

    segmentTree seg;
    vll empty(N);
    seg.build(empty, N);

    vll ans(Q);
    ll it = 0;
    stack<pll> st;

    for(int i=N-1; i>=0; i--){
        ll cant = 1;
        while(!st.empty() && vl[st.top().first] < vl[i]){
            cant += st.top().second;
            ll dif = vl[i] - vl[st.top().first];
            seg.update(st.top().first, st.top().first + st.top().second, dif);
            //cout << "upd; " << st.top().first << ' ' << st.top().first + st.top().second << ' ' << dif << '\n';
            st.pop();
        }
        st.push({i,cant});


        while(it < Q && vq[it].first.first == i){
            ans[vq[it].second] = seg.query(vq[it].first.first, vq[it].first.second);
            //cout << ans[vq[it].second] << ' ' << vq[it].first.first << ' ' << vq[it].first.second << '\n';
            it++;
        }
    }
    for(int i=0; i<Q; i++) cout << ans[i] << '\n';
}
