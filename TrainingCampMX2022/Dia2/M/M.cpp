#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

struct segmentTreeMax{
    vector<pll> st;
    ll n;
    segmentTreeMax(){
        st = vector<pll>();
        n=0;
    }
    pll func(pll a, pll b){ return max(a,b); }
    void build(vll& vl, int sizn){
        n = sizn;
        st.clear();
        st.resize(2*n);
        for(int i=0;i<n;i++){
            st[i+n].first = vl[i];
            st[i+n].second = i;
        }
        for(int i=n-1;i>0;i--){
            st[i]=func(st[i*2],st[i*2+1]);
        }
    }

    void update(int pos, ll x){
        pos+=n;
        st[pos].first = x; 
        pos/=2;
        while(pos){
            st[pos] = func(st[pos*2],st[pos*2+1]);
            pos/=2;
        }
    }

    pll query(int l, int r, pll def){
        pll ansl=def;
        pll ansr=def;
        for(l+=n,r+=n;l<r;l/=2,r/=2){
            if(l%2) ansl=func(ansl,st[l++]);
            if(r%2) ansr=func(st[--r],ansr);
        }
        return func(ansl,ansr);
    }
};
struct segmentTreeMin{
    struct str{
        ll first;
        ll second;
        str(){
            first = 0;
             second = 0;
        }
        str(ll aa, ll bb){
             first= aa;
             second= bb;
        }
    };
    vector<str> st;
    ll n;
    str func(str a, str b){ 
        return (a.first < b.first ? a : b);
    }
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

    void update(int pos, str x){
        pos+=n;
        st[pos] = x; 
        pos/=2;
        while(pos){
            st[pos] = func(st[pos*2],st[pos*2+1]);
            pos/=2;
        }
    }

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

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N,a,b; cin>>N>>a>>b;
        a--;b--;
        vll vl(N);
        vll ps(N);
        vll pr(N);
        for(int i=0; i<N; i++) cin>>vl[i];
        for(int i=0; i<N; i++) ps[i]=i+vl[i];
        for(int i=0; i<N; i++) pr[i]=i-vl[i];
        segmentTreeMax stMax;
        segmentTreeMin stMin;
        stMax.build(ps, N);
        stMin.build(pr, N);
        queue<pll> q;
        vll vis(N);
        vis[a]=1;
        q.push({a,0});
        ll ans=-1;
        while(!q.empty()){
            pll x = q.front();
            q.pop();
            ll n = x.first;
            ll i = x.first;
            ll t = x.second;
            if(n == b) {
                ans = t;
                break;
            }
            t++;
            while(1){
                ll left = max(ll(0),i-vl[i]);
                ll right = i+1;
                pll nex = stMax.query(left,right,{-100,-100});
                if(nex.first >= i){
                    stMax.update(nex.second, -100);
                    if(!vis[nex.second]){
                        q.push({nex.second,t});
                        vis[nex.second]=1;
                    }
                }else{
                    break;
                }
            }
            while(1){
                ll left=i+1;
                ll right=min(i+vl[i]+1,N);
                auto nex = stMin.query(left,right,{i+100,-100});
                if(nex.first <= i){
                    stMin.update(nex.second, {N+100,nex.second});
                    if(!vis[nex.second]){
                        q.push({nex.second,t});
                        vis[nex.second]=1;
                    }
                }else{
                    break;
                }
            }
        }
        cout << ans << '\n';
    }
}
