#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,a,b) for(int i=(a);i<(b);i++)
using vll = vector<ll>;


class FenwickTree{
	
	#define LSOne(S) ((S) & -(S)) 
	
	//funciona de [1, n]
	// funciona c++11, 14, 17
	private:
	  vll ft;                                        // internal FT is an array
	public:
	  FenwickTree(int m) { ft.assign(m+1, 0); }      // create an empty FT
	
	  void build(const vll &f) {
	    int m = (int)f.size()-1;                     // note f[0] is always 0
	    ft.assign(m+1, 0);
	    for (int i = 1; i <= m; ++i) {               // O(m)
	      ft[i] += f[i];                             // add this value
	      if (i+LSOne(i) <= m)                       // i has parent
	        ft[i+LSOne(i)] += ft[i];                 // add to that parent
	    }
	  }
	
	  FenwickTree(const vll &f) { build(f); }        // create FT based on f

	  ll rsq(int j) {                                // returns RSQ(1, j)
	    ll sum = 0;
	    for (; j; j -= LSOne(j))
	      sum += ft[j];
	    return sum;
	  }
	
	 // [i, j] inclusive
	  ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } // inc/exclusion
	
	  // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
	  void update(int i, ll v) {
	    for (; i < (int)ft.size(); i += LSOne(i))
	      ft[i] += v;
	  }
};


class RUPQ {                                     // RUPQ variant
	private:
	  FenwickTree ft;                                // internally use PURQ FT
	public:
	  RUPQ(int m) : ft(FenwickTree(m)) {}
	  void range_update(int ui, int uj, ll v) {
	    ft.update(ui, v);                            // [ui, ui+1, .., m] +v
	    ft.update(uj+1, -v);                         // [uj+1, uj+2, .., m] -v
	  }                                              // [ui, ui+1, .., uj] +v
	  ll point_query(int i) { return ft.rsq(i); }    // rsq(i) is sufficient
	};
	
	class RURQ  {                                    // RURQ variant
	private:                                         // needs two helper FTs
	  RUPQ rupq;                                     // one RUPQ and
	  FenwickTree purq;                              // one PURQ
	public:
	  RURQ(int m) : rupq(RUPQ(m)), purq(FenwickTree(m)) {} // initialization
	  void range_update(int ui, int uj, ll v) {
	    rupq.range_update(ui, uj, v);                // [ui, ui+1, .., uj] +v
	    purq.update(ui, v*(ui-1));                   // -(ui-1)*v before ui
	    purq.update(uj+1, -v*uj);                    // +(uj-ui+1)*v after uj
	  }
	  ll rsq(int j) {
	    return rupq.point_query(j)*j -               // optimistic calculation
	           purq.rsq(j);                          // cancelation factor
	  }
	  ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } // standard
};


namespace seg{
    // add to range, assign to range, get range sum
    enum OpType { add, set };
    struct Op{ OpType type; ll val; };
    Op eye={OpType::add,0};
    Op combine(Op a, Op b) { // a_time < b_time
        if(b.type==OpType::set) return b;
        return {a.type, a.val+b.val};
    }
    ll apply(Op op, ll prev, int l, int r) {
        return op.type==OpType::add ? prev+op.val*(r-l) : op.val*(r-l); 
    }
    const int N=1<<19; ll st[N*2]; Op lazy[N*2];
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
        st[p]=st[p*2]+st[p*2+1];
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
            if(l&1) ans+=st[l++];
            if(r&1) ans+=st[--r];
        }
        return ans;
    }
    void build(int n, vll& A) {
        rep(i,0,n) st[i+N]=A[i];
        rep(i,1,N) st[i]=st[i*2]+st[i*2+1];
        rep(i,1,2*N) lazy[i]=eye;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll N, Q;
    cin >> N >> Q;
    vll vl(N);
    RURQ fen(N);
    //seg::build(N, vl); 
    for(int i=0; i<N; i++) cin>>vl[i];

    while(Q--){
        ll K; cin >> K;
        ll cc = 0;
        
        stack<int> sa, sb, sc;
        while(K--){
            ll a,b,c;
            cin >> a >> b >> c;
            a--;
            cc += (b-a)*c;
            
            fen.range_update(a+1,b,c);  
            sa.push(a+1); sb.push(b); sc.push(c*-1);      
        }
        
        
        ll mid = (cc+1)/2;
        ll iii = 63 - __builtin_clzll(N);
        ll inc = (ll(1) << iii);
        ll ini = 0;
        while(inc != 0){
            if(ini + inc >= N || fen.rsq(ini + inc) >= mid) inc/=2;
            else ini+=inc;
        }
        ini++;
        if(cc%2 == 1){
            cout << vl[ini-1] << '\n';
            while(!sa.empty()){
                ll aa , bb, cc;
                aa = sa.top();
                bb = sb.top();
                cc = sc.top();
                sa.pop();
                sb.pop();
                sc.pop();
                fen.range_update(aa,bb,cc);
            }
            //seg::update(0,N, seg::Op{seg::OpType::set, 0});
            continue;
        }
        mid++;
        inc = (ll(1) << iii);
        double ans = vl[ini-1];
        ini = 0;

        while(inc != 0){
            if(ini + inc >= N || fen.rsq(ini + inc) >= mid) inc/=2;
            else ini+=inc;
        }
        ini++;
        //seg::update(0,N, seg::Op{seg::OpType::set, 0});
        while(!sa.empty()){
                ll aa , bb, cc;
                aa = sa.top();
                bb = sb.top();
                cc = sc.top();
                sa.pop();
                sb.pop();
                sc.pop();
                fen.range_update(aa,bb,cc);
            }
        ans += vl[ini-1];
        ans /= 2;
        cout << fixed << setprecision(1) << ans << '\n';
    }
}
    