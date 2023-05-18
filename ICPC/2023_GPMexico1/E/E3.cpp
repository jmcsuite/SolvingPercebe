#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define fast cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);
#define lsb(x) ((x)&(-x))
#define nl '\n'
 
using namespace std;

const ll maxn = 4e5+5;
const ll neut = 0;
const ll lzneut = 0;
const ll INF = (1e16)*-1; // use -inf not inf
const ll tope = 1e9;
ll disc = 1;
ll a[maxn],clo[maxn];
vector < ll > sub,ind,vind,ans,chi;
vector < vector <ll> > adj;

void init(ll n){
    sub.assign(n+5,0LL);
    chi.assign(n+5,0LL);
    ind.assign(n+5,-1LL);
    vind.assign(n+5,-1LL);
    ans.assign(n+5,-1LL);
    adj.resize(n+5);
}

void dfs(ll node){
    ind[node] = disc;
    vind[disc] = node;
    disc++;
    for (auto signode : adj[node]) dfs(signode);
    clo[node] = disc;
}

struct STree { // example: range sum with range addition
	vector<ll> lazy;ll n;
    vector < pair <ll,ll> > st;
	STree(ll n): st(4*n+5,{0LL,0LL}), lazy(4*n+5,lzneut), n(n) {} 
        // Esta inicializacion esta mal, usa --Wall para ver el error

	void build(ll node, ll ini, ll fin){
		lazy[node]=0;  // lazy neutral element
		if(ini+1==fin){
            st[node].first = a[vind[ini]];
            st[node].second = vind[ini];
            return;
        }
		ll mid =(ini+fin)/2;
		build(2*node,ini,mid);
        build(2*node+1,mid,fin);
        if (st[node*2].first < st[2*node + 1].first){
            st[node].first = st[node*2].first;
            st[node].second = st[node*2].second;
        }
        else{
            st[node].first = st[2*node + 1].first;
            st[node].second = st[2*node + 1].second;
        }
	}
	void push(ll node, ll ini, ll fin){
		if(lazy[node] == lzneut) return; 
		st[node].first -= lazy[node]; // update st according to lazy
		if(ini+1<fin){ // propagate to children
            lazy[2*node] += lazy[node];
			lazy[2*node + 1] += lazy[node];
		}
		lazy[node]=0; // clear node lazy
	}
	void upd(ll node, ll ini, ll fin, ll l, ll r, ll val){
		push(node,ini,fin);
		if(ini>=r||fin <=l)return;
		if(ini>=l&& fin <=r){
            lazy[node] += val;
			push(node,ini,fin);
            return;
		}
		ll mid =(ini+fin)/2;
		upd(2*node,ini,mid,l,r,val);upd(2*node+1,mid,fin,l,r,val);
		if (st[node*2].first < st[2*node + 1].first){
            st[node].first = st[node*2].first;
            st[node].second = st[node*2].second;
        }
        else{
            st[node].first = st[2*node + 1].first;
            st[node].second = st[2*node + 1].second;
        }
	}
	pair <ll,ll> query(ll node, ll ini, ll fin, ll l, ll r){
		if(ini>=r || fin <= l)return {1,0}; // operation neutral
		push(node,ini,fin);
		if(ini>=l&&fin<=r)return st[node];
		ll mid =(ini+fin)/2;
        pair <ll,ll> lft = query(2*node,ini,mid,l,r);
        pair <ll,ll> rgt = query(2*node + 1,mid,fin,l,r);
		if (lft.first < rgt.first) return lft;
        return rgt;
	}
	void build(){build(1,0,n+1);} //it is actually [1, n]
	void upd(ll l, ll r, ll val){upd(1,0,n+1,l,r,val);} //remember the n is non inclusive
	pair <ll,ll> query(ll l, ll r){return query(1,0,n+1,l,r);} //remember the n is non inclusive
}; // usage: STree rmq(n);rmq.init(x);rmq.upd(s,e,v);rmq.query(s,e);



int main(){
    fast;
    ll n,q,pos,val;
    cin>>n>>q;
    init(n);
    for (ll i = 1; i<=n; i++) cin>>a[i];

    for (ll i = 1; i<n; i++){
        ll x,y;
        cin>>x>>y;
        adj[x].pb(y);
        chi[x]++;
        sub[y]++;
    }
    for (ll i = 1; i<=n; i++){
        if (chi[i] > 0 && sub[i] == 0 || n == 1) dfs(i); // esto tambien esta rancio, pero funciona por suerte creo, los casos 
                                                         // estan debiles, todos los arboles tienen root 1
    }
    
    STree st(n);
    st.build();
    for (ll qin = 1; qin<=q; qin++){
        cin>>pos>>val;
        ll l = ind[pos];
        ll r = clo[pos];
        ll tam = r-l;
        ll uval = val/tam;
        //cout<<"Update: "<<l<<" "<<r<<" "<<uval<<nl;
        st.upd(l,r,uval);

        if (val%tam != 0){
            ll nol= ind[pos];  // You are changing l, r
            ll nor = ind[pos]+1;
            ll uval = val%tam; //val%tam, not val
            //cout<<"Update: "<<l<<" "<<r<<" "<<uval<<nl;
            st.upd(nol,nor,uval);
        }
        while(true){
            pair <ll,ll> minic = st.query(l,r);
            ll minval = minic.first;
            ll minpos = minic.second;
            //cout<<qin<<": "<<minval<<" "<<minpos<<nl;
            if (minval > 0) break;

            if (ans[minpos] == -1) ans[minpos] = qin;
            st.upd(ind[minpos],ind[minpos]+1,INF);
        }
    }
    for (ll i = 1; i<=n; i++){
        if (ans[i] == -1) cout<<-1<<nl; // ???? WTF MURO
        else cout<<ans[i]<<nl;
    }
    return 0;
}
