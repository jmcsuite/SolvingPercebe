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
ll primos[maxc];
ll prcant=0;
vpll cribPrecomp[maxc];

void build(){
    criba[1]=1;
    for(int i=2; i<maxc; i++){
        if(criba[i] == 0) primos[prcant++]=i;
        if(criba[i] == 0) criba[i]=i;
        for(int j=0; j<prcant && (primos[j]*i)<maxc; j++){
            criba[primos[j]*i]=primos[j];
            if(i%primos[j] == 0) break;
        }
    }
}


namespace tree{
    vll vadj[maxn];
    ll vis[maxn];
    ll in[maxn];
    ll out[maxn];
    ll dfspath[2*maxn];
    ll val[maxn];
    ll n=0;
    ll idx=0;

    ll depth[2*maxn];
    ll depthAns[2*maxn];
    ll f1[maxn];
    ll i2=0;

    const int maxPow=18;
    ll dpVal[2*maxn][maxPow];
    ll dpAns[2*maxn][maxPow];
    


    void clear(){
        for(int i=0; i<n; i++){
            vadj[i].clear();
            vis[i] = 0;
        }
        n=0;
        idx=0;
        i2=0;
    }

    void build(ll x, ll p, ll d=0){
        in[x]=idx;
        dfspath[idx]=x;

        depth[i2]=d;
        depthAns[i2]=x;
        f1[x]=i2;
        i2++;

        idx++;
        for(ll y: vadj[x]){
            if(y == p) continue;
            build(y, x,d+1);
            depth[i2]=d;
            depthAns[i2]=x;
            i2++;
        }
        out[x]=idx;
        dfspath[idx]=x;
        idx++;

        
    }

    void buildPow(ll N){
        for(int i=0; i<(2*N-1); i++){
            dpAns[i][0]=depthAns[i];
            dpVal[i][0]=depth[i];
        }
        for(int j=1; j<maxPow; j++){
            for(int i=0; i<(2*N-1); i++){
                dpAns[i][j]=dpAns[i][j-1];
                dpVal[i][j]=dpVal[i][j-1];
                int nex = i+(1<<(j-1));
                if(nex >= 2*N-1) continue;
                if(dpVal[nex][j-1] < dpVal[i][j]){
                    dpVal[i][j]=dpVal[nex][j-1];
                    dpAns[i][j]=dpAns[nex][j-1];
                }
            }
        }
    }

    ll query(ll a, ll b){
        ll pa=f1[a];
        ll pb=f1[b];ll fa= min(pa,pb); ll fb = max(pa,pb);
        ll dis = fb-fa+1;
        ll pp = 31-__builtin_clz(dis);
        ll nex = fb-(1<<pp)+1;
        ll ans = dpAns[fa][pp];
        if(dpVal[nex][pp] < dpVal[fa][pp]) return dpAns[nex][pp];
        return ans;
    }


}

void buildX(){
    for(int i=0; i<tree::n; i++){
        ll x = tree::val[i];
        ll orX = x;
        if(!cribPrecomp[orX].empty()) continue;
        while(x!=1){
            ll nx = x;
            ll cc = 0;
            while(criba[nx] == criba[x]){
                cc++;
                nx/=criba[x];
            }
            cribPrecomp[orX].push_back({criba[x],cc});
            x = nx;
        }
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
        long long nexAns = currAns;
        for(pll pp: cribPrecomp[x]){
            ll p = pp.first;
            nexAns = (nexAns*inv[fact[p]+1])%mod;
        }

        for(pll pp: cribPrecomp[x]){
            fact[pp.first]+=dif*pp.second;
        }

        for(pll pp: cribPrecomp[x]){
            ll p = pp.first;
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

    void move(pll q){
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
            ll lca = tree::query(s.second, s.first);
            if(lca == s.second){
                ll ans = print();
                allAns[queries[i].first.second]=ans;
                continue;
            }
            if(lca == s.first){
                ll ans = print();
                allAns[queries[i].first.second]=ans;
                continue;
            }
            realAdd(lca,1);
            ll ans = print();
            realAdd(lca,-1);
            allAns[queries[i].first.second]=ans;
        }
    }
}

pll transform(pll x, ll idx){
    ll l = tree::query(x.first, x.second);
    if(l == x.first){
        ll izq  = tree::in[l];
        ll der = tree::in[x.second];
        return {izq, der};
    }
    if(l == x.second){
        ll izq = tree::in[l];
        ll der = tree::in[x.first];
        return {izq,der};
    }
    if(tree::out[x.first] < tree::in[x.second]){
        ll izq = tree::out[x.first];
        ll der = tree::in[x.second];
        return {izq,der};
    }
    ll izq = tree::out[x.second];
    ll der = tree::in[x.first];
    return {izq,der};
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

bool cm(pair<pll,pll>& x, pair<pll,pll>& y){
    if(x.first.first != y.first.first) return x.first.first<y.first.first;
    if(x.first.first % 2) return x.second.second>y.second.second;
    return x.second.second < y.second.second;
};

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

        buildX();

        vpll queries(Q);
        for(int i=0; i<Q; i++) cin>>queries[i].first>>queries[i].second;
        for(int i=0; i<Q; i++){
            queries[i].first--;
            queries[i].second--;
        }

        tree::build(0,0);
        tree::buildPow(N);


        ll s = sqrt(N);
        for(int i=0; i<Q; i++){
            mo::queries[i].second = transform(queries[i],i);
            mo::queries[i].first.first = mo::queries[i].second.first/s;
            mo::queries[i].first.second = i;
        }


        mo::q=Q;
        
        sort(mo::queries, mo::queries+Q,cm);
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

        
        if(0 == T) return 0; 
        mo::clear();
        tree::clear();
    }
}
