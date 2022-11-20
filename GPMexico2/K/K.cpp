#include <bits/stdc++.h>
 
#define MAX 10e15+1
#define MIN -10e15+1
#define MOD 998244353
#define FOR(i, a, b)    for(long long i=a;i<b;i++)
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define per(i,a,b) for(int i=(b-1);i>=(a);i--)
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef pair<ll,ll> pll;
typedef pair<double,double> ii;
typedef vector<pll> vpll;
vll v1,v2;
ll M,K,Q,T;
vll vl;
vector<vll> vadj;
ll mod = 1e9+7;

// funciona con c++ 11, 14, 17
/* Segment Tree con range updates y range queries
 * los updates/queries son de [0, N-1]
 * Recordatorio: LazyPropagation lo unico que hace es guardar un valor
 * en el array lazy, que puede llegar a ser utilizado. Sin embargo
 * no se asegura que se use antes de que se acutalize con un nuevo valor
 *
 */
// add to range, assign to range, get range sum
enum OpType { add, set };
struct Op{ OpType type; ll val; };
Op eye={OpType::add,0};
Op combine(Op a, Op b) { // a_time < b_time
    if(b.type==OpType::set) return b;
    return {a.type, (a.val+b.val)%mod};
}
pll apply(Op op, pll prev, int l, int r) {
	ll dis = r-l;
	pll ans;
	ans.second = prev.second%mod + dis*op.val%mod;
	ans.second%=mod;
	ans.first = ((op.val*op.val)%mod)*dis%mod + prev.first + (2*prev.second*op.val)%mod;
	ans.first%=mod;
	//cout << l << ' ' << r << ' ' << prev.first << ' ' << prev.second << ' ' << ans.first << ' ' << ans.second << endl;
	return ans;
    //return op.type==OpType::add ? prev+op.val*(r-l) : op.val*(r-l); 
}
const int N=1<<18; vpll st(N*2); Op lazy[N*2];
void prop(int L, int R, int p, int l, int r) {
    st[p]=apply(lazy[p],st[p],l,r);
    if(p<N) {
        lazy[2*p]=combine(lazy[2*p],lazy[p]);
        lazy[2*p+1]=combine(lazy[2*p+1],lazy[p]);
    }
    lazy[p]=eye;
    if(L<=l&&r<=R||r<=L||R<=l) return;
    int m=(l+r)/2;
    prop(L,R,2*p,l,m);
    prop(L,R,2*p+1,m,r);
    st[p].second=(st[p*2].second+st[p*2+1].second)%mod;
	st[p].first=(st[p*2].first+st[p*2+1].first)%mod;
}
void update(int L, int R, Op op){
    prop(L,R,1,0,N);
    for(int l=L+N,r=R+N;l<r;l/=2,r/=2) {
        if(l&1) lazy[l++]=op;
        if(r&1) lazy[--r]=op;
    }
    prop(L,R,1,0,N);
}
ll query(int l, int r) {
    prop(l,r,1,0,N);
    ll ans=0;
    for(l+=N,r+=N;l<r;l/=2,r/=2) {
		if(l&1) ans+=st[l++].first;
		if(r&1) ans+=st[--r].first;
		ans%=mod;
    }
    return ans;
}
void build(int n, vpll A) {
    rep(i,0,n) st[i+N].first=A[i].first;
    per(i,1,N) st[i].first=(st[i*2].first+st[i*2+1].first);
	rep(i,0,n) st[i+N].second=A[i].second;
    per(i,1,N) st[i].second=(st[i*2].second+st[i*2+1].second);
    rep(i,1,2*N) lazy[i]=eye;
}



int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
    vpll A;
	ll NN;
    cin >> NN >> Q;
    A.resize(NN);
    FOR(i,0,NN) cin >> A[i].second;
    FOR(i,0,NN) A[i].first = (A[i].second*A[i].second)%mod;

    build(NN, A);
   

    while(Q--){
        char a;
        cin >> a;
        if(a == 'u'){
            ll b,c,d;
            cin >> b >> c >> d;
            b--;
			update(b,c,{OpType::add, d});
            //seg.update(b, c, d);
        }else{
            ll b,c;
            cin>>b>>c;
            b--; 
			//cout << query(0,5) << endl;
            ll ans = query(b,c);
            //cout << seg.RMQ(0,4).first << endl;
            cout << (ans%mod+mod)%mod << '\n';
        }
    }
}
