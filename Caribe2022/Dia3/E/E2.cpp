#include<bits/stdc++.h>
using namespace std;
using ll = int;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

long long mod=1000000007;
const long long maxc=1000002;
const long long maxn=100005;

ll criba[maxc];

void build(){
    criba[1]=1;
    for(long long i=1; i<maxc; i++){
        if(criba[i]) continue;
        criba[i] = i;
        for(long long j=i; j*i < maxc; j++){
            criba[i*j]=i;
        }
    }
}




namespace tree{
    vll vadj[maxn];
    vpll queries[maxn];
    ll vis[maxn];
    ll in[maxn];
    ll out[maxn];
    ll dfspath[2*maxn];
    ll val[maxn];
    ll n=0;
    ll lca[maxn];
    ll idx=0;

    ll vl[maxn];
    ll sz[maxn];
    ll rep[maxn];



    void clear(){
        for(int i=0; i<n; i++){
            vadj[i].clear();
            queries[i].clear();
            vis[i] = 0;
        }
        n=0;
        idx=0;
    }

    ll find(ll x){
        if(x == vl[x]) return x;
        return find(vl[x]);
    }

    void un(ll p, ll x){
        ll pp = find(p);
        ll xx = find(x);
        if(pp == xx) return;
        if(sz[pp] >= sz[xx]){
            vl[xx] = pp;
            if(sz[pp] == sz[xx]) sz[pp]++;
        }else{
            rep[xx] = rep[pp];
            vl[pp] = vl[xx];
        }
    }

    void build(ll x, ll p){
        in[x]=idx;
        dfspath[idx]=x;
        idx++;
        for(ll y: vadj[x]){
            if(y == p) continue;
            build(y, x);
        }
        out[x]=idx;
        dfspath[idx]=x;
        idx++;
    }

    void get(ll x, ll p){
        for(pll yy: queries[x]){
            ll y = yy.first;
            ll i = max(x,y);
            ll j = min(x,y);
            pll q(i,j);
            if(y == x) lca[yy.second] = x;
            if(vis[y]) lca[yy.second] = rep[find(y)];
        }

        vis[x]=1;
        vl[x]=x;
        rep[x]=x;
        sz[x]=1;
        for(ll y: vadj[x]){
            if(y == p) continue;
            get(y,x);
        }
        un(p,x);
    }
}
const int maxinv = 20*maxn;
long long inv[maxinv];


namespace mo{
    pair<pll,pll> queries[maxn];
    int q;
    long long fact[maxc];
    ll ncount[maxc];
    ll allAns[maxn];
    ll izq=0;
    ll der=0;
    long long currAns=1;

    void clear(){
        izq=0;
        der=0;
        currAns=1;
        for(int i=0; i<maxc; i++) fact[i] = ncount[i] = 0;
    }

    ll print(){
        return currAns;
    }



    void realAdd(ll idx, ll dif){
        ll x = tree::val[idx];
        ll cx = x;
        set<ll> primos;
        while(cx!=1){
            primos.insert(criba[cx]);
            cx = cx/criba[cx];
        }
        long long nexAns = currAns;
        for(ll p: primos){
            nexAns = (nexAns*inv[fact[p]+1])%mod;
        }

        while(x!=1){
            fact[criba[x]]+=dif;
            x/=criba[x];
        }

        for(ll p: primos){
            nexAns = (nexAns*(fact[p]+1))%mod;
        }
        currAns = nexAns;
    }

    void add(ll idx, ll dcount){
        ll dif=1;
        ncount[idx]+=dcount;
        if(ncount[idx]%2==0){
            dif=-1;
        }
        realAdd(idx,dif);
    }

    void move(pll& q){
        ll j = q.second;
        ll i = q.first;
        while(der < j) add(tree::dfspath[++der], 1);
        while(izq > i) add(tree::dfspath[--izq], 1);
        while(der > j) add(tree::dfspath[der--], -1);
        while(izq < i) add(tree::dfspath[izq++], -1);
        
    }

    void solve(){
        for(int i=0; i<q; i++){
            pll p = queries[i].second;
            move(p);
            pll s(tree::dfspath[p.first], tree::dfspath[p.second]);
            ll tmp = s.second;
            s.second = min(s.second, s.first);
            s.first = max(s.first, tmp);
            if(tree::lca[queries[i].first.second] == s.second){
                ll ans = print();
                allAns[queries[i].first.second]=ans;
                continue;
            }
            if(tree::lca[queries[i].first.second] == s.first){
                ll ans = print();
                allAns[queries[i].first.second]=ans;
                continue;
            }
            realAdd(tree::lca[queries[i].first.second],1);
            ll ans = print();
            realAdd(tree::lca[queries[i].first.second],-1);
            allAns[queries[i].first.second]=ans;
        }
    }
}

pll transform(pll& x, ll idx){
    ll tmp = x.second;
    x.second = min(x.second, x.first);
    x.first = max(tmp, x.first);
    pll y;
    ll l = tree::lca[idx];
    if(l == x.first){
        y.first = min(tree::in[l],tree::in[x.second]);
        y.second = max(tree::in[x.second],tree::in[l]);
        return y;
    }
    if(l == x.second){
        y.first = min(tree::in[l], tree::in[x.second]);
        y.second = max(tree::in[x.first], tree::in[l]);
        return y;
    }
    if(tree::out[x.first] < tree::in[x.second]){
        y.first = tree::out[x.first];
        y.second = tree::in[x.second];
        return y;
    }
    y.first = tree::out[x.second];
    y.second = tree::in[x.first];
    return y;
}

long long bin_exp(long long a, long long x){
    long long ans=1;
    while(x){
        if(x%2) ans = (ans*a)%mod;
        a = (a*a)%mod;
        x/=2;
    }
    return ans;
}

long long fact[maxinv];
long long invFact[maxinv];
void buildInv(){
    fact[1]=1;
    inv[1]=1;
    for(int i=2; i<maxinv; i++) fact[i] = (fact[i-1]*i)%mod;
    invFact[maxinv-1] = bin_exp(fact[maxinv-1],mod-2);
    for(int i=maxinv-2; i>=1; i--) invFact[i] = ((i+1)*invFact[i+1])%mod;
    for(int i=2; i<maxinv; i++) inv[i] = (fact[i-1]*invFact[i])%mod;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    buildInv();
    ll T; cin>>T;
    build();
    while(T--){
        ll N; cin>>N;
        tree::n = N;
        for(int i=0; i<N-1; i++){
            ll a,b; cin>>a>>b; a--; b--;
            tree::vadj[a].push_back(b);
            tree::vadj[b].push_back(a);
        }
        for(int i=0; i<N; i++){
            cin>>tree::val[i];
        }
        ll Q; cin>>Q;

        vpll queries(Q);
        for(int i=0; i<Q; i++) cin>>queries[i].first>>queries[i].second;
        for(int i=0; i<Q; i++){
            queries[i].first--;
            queries[i].second--;
            ll tmp=queries[i].first;
            queries[i].first = max(queries[i].first,queries[i].second);
            queries[i].second = min(queries[i].second, tmp);
            tree::queries[queries[i].first].push_back({queries[i].second,i});
            tree::queries[queries[i].second].push_back({queries[i].first,i});
        }

        tree::build(0,0);
        tree::get(0,0);


        ll s = sqrt(N);
        for(int i=0; i<Q; i++){
            mo::queries[i].second = transform(queries[i],i);
            mo::queries[i].first.first = mo::queries[i].second.first/s;
            mo::queries[i].first.second = i;
        }


        mo::q=Q;
        
        sort(mo::queries, mo::queries+Q, [](pair<pll,pll>& x, pair<pll,pll>& y){
                if(x.first.first != y.first.first) return x.first.first<y.first.first;
                if(x.first.first % 2) return x.second.second>y.second.second;
                return x.second.second < y.second.second;
                });



        mo::add(0,1);

        mo::solve();
        for(int i=0; i<Q; i++) cout << mo::allAns[i] << '\n';

        /*cout << "DFS PATH" << endl;
        for(int i=0; i<2*N; i++){
            cout << tree::dfspath[i] << ' ';
            cout << endl;
        }
        cout << "Queries" << endl;
        for(int i=0; i<Q; i++){
            cout << mo::queries[i].first.first << ' ' << mo::queries[i].first.second << '\n';
        }*/
        
        
        mo::clear();
        tree::clear();
    }
}

