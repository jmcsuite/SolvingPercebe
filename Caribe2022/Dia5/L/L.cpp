#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=1<<20;
using bbi=ll;

using rp = pair<ll,pll>;

 rp mygcd(ll a, ll b){
     if(a==0) return {b,{0,1}};
     if(b==0) return {a,{1,0}};
     rp prev=mygcd(b%a,a);

     ll ax=prev.second.second-prev.second.first*(b/a);
     ll bx=prev.second.first;

     rp ans={prev.first, {ax,
         bx}};
     return ans;
 }

 rp solve(ll c1, ll c2, ll b){
     rp ans = mygcd(c1,c2);
     if(b%ans.first != 0) return {-1,{-1,-1}};
     ll bd = b/ans.first;
     ll c2p = c2/ans.first;

     ans.second.first%=c2p;
     bd%=c2p;

     ans.second.first = (__int128(bd)*__int128(ans.second.first))%c2p;
     ans.second.first = (ans.second.first+c2p)%c2p;
 
      ans.second.second = (b-ans.second.first*c1)/c2;
      return ans;
  }

struct str{
    ll b;
    ll c;
    bool f;
    ll sz;
    str(){
        b=0;
        c=1;
        f=false;
        sz=0;
    }
    str(ll bb, ll cc,bool ff=true){
        b=bb;
        c=cc;
        f=ff;
        sz=1;
    }
};
str st[2*maxn];


struct segmentTree{

    str func(str a, str b){
        if(a.f == false || b.f == false) return {0,1,false};
        rp tmp = solve(a.c,b.c, b.b-a.b);
        if(tmp.first == -1) return {0,1,false};
        ll gc = b.c/tmp.first;
        gc = gc*a.c;
        //lcm
        bbi pi = bbi(a.c)*bbi(tmp.second.first);
        bbi ab = a.b;
        bbi ggc = gc;
        bbi tot = (pi%ggc + ab)%ggc;
        
        str ans(tot,gc);
        ans.sz=a.sz+b.sz;
        return ans;
    }

    ll n;

    void build(vll& b, vll& c, int sizn){
        n=sizn;
        for(int i=0; i<n; i++){
            st[i+n].b=b[i];
            st[i+n].c=c[i];
            st[i+n].f=true;
            st[i+n].sz=1;
        }
        for(int i=n-1; i>0; i--){
            st[i]=func(st[i*2],st[i*2+1]);
        }
    }

    str query(int l, int r){
        str ansl;
        str ansr;
        ansl.b=0; ansl.c=1; ansl.f=true; ansl.sz=0;
        ansr.b=0; ansr.c=1; ansr.f=true; ansr.sz=0;
        for(l+=n, r+=n; l<r; l/=2,r/=2){
            if(l%2) ansl=func(ansl,st[l++]);
            if(r%2) ansr=func(st[--r],ansr);
        }
        return func(ansl,ansr);
    }

};

ll solve(vll& bs, vll& cs){
    segmentTree myst; myst.build(bs,cs,bs.size());
    /*for(size_t i=0; i<bs.size(); i++) cout << bs[i] << ' ';
    cout << endl;
    for(size_t i=0; i<cs.size(); i++) cout << cs[i] << ' ';
    cout << endl;*/
    ll N=bs.size();
    ll izq=0;
    ll der=0;
    ll ans=0;
    while(izq<N){
        auto q=myst.query(izq,der);
        //cout << izq << ' ' << der << ' ' << q.f << endl;
        if(q.f) ans=max(ans,der-izq);
        if(q.f && der < N) der++;
        else izq++;
    }
    //cout << "end debug" << endl;

    return ans;
}


map<ll,ll> pos[maxn];
using seg = pair<ll,pll>;
set<ll> setst[maxn];

ll dfs(ll x, ll i){
    if(setst[i].find(x) == setst[i].end()) return 0;
    setst[i].erase(x);
    return 1 + dfs(x,i+1);
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin>>N>>M;
    vll cs(N);
    for(int i=0; i<N; i++){
        cin>>cs[i];
        for(int j=0; j<cs[i]; j++){
            ll x; cin>>x;
            setst[i].insert(x);
            pos[i][x]=j;
        }
    }

    vector<seg> allSegs;
    for(int i=0; i<N; i++){
        while(!setst[i].empty()){
            ll x=*setst[i].begin();
            ll t = dfs(x,i);
            allSegs.push_back({x,{i,t}});
        }
    }

    vll ans(M+1);
    for(seg& mys: allSegs){
        //cout << "Segment: " << mys.first << ' ' << mys.second.first << ' ' << mys.second.second << endl;
        vll bbs(mys.second.second);
        vll ccs(mys.second.second);
        ll x=mys.first;
        for(int i=0,j=mys.second.first; i<mys.second.second; i++,j++){
            ccs[i]=cs[j];
            bbs[i]=pos[j][x];
        }
        ll tmp = solve(bbs,ccs);
        ans[x]=max(ans[x],tmp);
    }

    for(int i=1; i<=M; i++) cout << ans[i] << '\n';
}


