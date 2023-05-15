#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=1<<21;

/*using rp = pair<ll,pll>;
rp mygcd(ll a, ll b){
    if(a==0) return {b,{0,1}};
    if(b==0) return {a,{1,0}};
    rp prev=mygcd(b%a,a);
    ll ax=prev.second.second-prev.second.first*(b/a);
    ll bx=(prev.first-a*ax)/b;
    rp ans={prev.first, {ax,bx}};
    return ans;
}

rp solve(ll c1, ll c2, ll b){
    rp ans=mygcd(c1,c2);
    if(b%ans.first != 0) return {-1,{-1,-1}};
    ll bd = b/ans.first;
    ll c2p= c2/ans.first;
    bd%=c2p;
    ans.second.first%=c2p;
    ans.second.first *= bd;
    ans.second.first = (ans.second.first%(c2p)+c2p)%c2p;
    ans.second.second = (b-ans.second.first*c1)/c2;
    return ans;
}*/

struct str{
    ll b;
    ll c;
    bool f;
    str(){
        b=0;
        c=1;
        f=true;
    }
    str(ll bb, ll cc,bool ff=true){
        b=bb;
        c=cc;
        f=ff;
    }
};
str st[2*maxn];


tuple<ll, ll, ll> extendedGcd (ll a, ll b) {
	if (b == 0) {
		if (a > 0) return {a, 1, 0};
		return {-a, -1, 0};
	} else {
		auto [d, x, y] = extendedGcd(b, a % b);
		return {d, y, x - y * (a / b)};
	}
}
 
 

using bin = __int128;
pair<ll, ll> crt (ll x, ll mod, ll a, ll m) {
	if (x == -1 || a == -1) return {-1, -1};
	
	auto [d, s, t] = extendedGcd(mod, -m);
	if ((a - x) % d != 0) return {-1, -1};
	ll step = m / d;
        bin ss = s;
        bin ax = (a-x)/d;
        bin sss=step;
        bin kk=ss*(ax)%step;
        kk%=step;
        ll k=kk;
        
	ll k = s * (((a - x) / d) % step) % step;
	if (k < 0) k += step;
	x += mod * k;
	mod *= step;
	
	return {x, mod};
}

struct segmentTree{

    str func(str a, str b){
        auto ans=crt(a.b,a.c,b.b,b.c);
        str sol(ans.first,ans.second);
        if((a.f == false) || (b.f == false)) sol.f=false;
        if(ans.second == -1) sol.f=false;
        return sol;
        /*rp tmp = solve(a.c,b.c, b.b-a.b);
        if(tmp.first == -1) return {0,1,false};
        ll gc = b.c/tmp.first;
        gc = gc*a.c;
        str ans((a.b+((a.c*tmp.second.first)%gc)%gc),gc);
        ans.sz=a.sz+b.sz;
        return ans;*/
    }

    ll n;

    void build(vll& b, vll& c, int sizn){
        n=sizn;
        assert((2*n-1)<maxn);
        for(int i=0; i<n; i++){
            st[i+n].b=b[i];
            st[i+n].c=c[i];
            st[i+n].f=true;
        }
        for(int i=n-1; i>0; i--){
            assert((i*2)<2*n);
            st[i]=func(st[i*2],st[i*2+1]);
        }
    }

    str query(int l, int r){
        str ansl;
        str ansr;
        ansl.b=0; ansl.c=-100; ansl.f=true; 
        ansr.b=0; ansr.c=-100; ansr.f=true; 
        assert(r+n <= 2*n);
        for(l+=n, r+=n; l<r; l/=2,r/=2){
            if(l%2) {
                if(ansl.c==-100){
                    ansl=st[l++];
                }else{
                    
                    ansl=func(ansl,st[l++]);
                }
            }
            if(r%2) {
                if(ansr.c==-100){
                    ansr=st[--r];
                }else{
                    ansr=func(st[--r],ansr);
                }
            }
        }
        if(ansl.c==-100) return ansr;
        if(ansr.c==-100) return ansl;
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
        assert(izq <= der);
        auto q=myst.query(izq,der);
        //cout << izq << ' ' << der << ' ' << q.f << endl;
        if(q.f) ans=max(ans,der-izq);
        if((q.f) && (der < N)) der++;
        else izq++;
    }
    //cout << "end debug" << endl;

    return ans;
}


const long long mmax=100010;
map<ll,ll> pos[mmax];
using seg = pair<ll,pll>;
set<ll> setst[mmax];

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


