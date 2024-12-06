#include <bits/stdc++.h>
#define ll long long
#define fore(i,a,b) for(ll i=a; i<b; i++)
#define nl '\n'
#define pb push_back
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define rofe(i,a,b) for(ll i=a-1; i>=b; i--)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
#define pii pair <ll,ll>
#define fst first
#define snd second

using namespace std;

typedef pair<ll,ll> ii;

// MAXN must be power of 2 !!
// MOD-1 needs to be a multiple of MAXN !!
// big mod and primitive root for NTT:
const ll MOD=998244353,RT=3,MAXN=1<<18; //watch out with RTEs (increase MAXN):
typedef vector<ll> poly;
// FFT
struct CD {
	double r,i;
	CD(double r=0, double i=0):r(r),i(i){}
	double real()const{return r;}
	void operator/=(const int c){r/=c, i/=c;}
};
CD operator*(const CD& a, const CD& b){
	return CD(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);}
CD operator+(const CD& a, const CD& b){return CD(a.r+b.r,a.i+b.i);}
CD operator-(const CD& a, const CD& b){return CD(a.r-b.r,a.i-b.i);}
const double pi=acos(-1.0);

CD cp1[MAXN+9],cp2[MAXN+9];
int R[MAXN+9];
void dft(CD* a, int n, bool inv){
	fore(i,0,n)if(R[i]<i)swap(a[R[i]],a[i]);
	for(int m=2;m<=n;m*=2){
		double z=2*pi/m*(inv?-1:1); // FFT
		CD wi=CD(cos(z),sin(z)); // FFT
		// CD wi=root(m,inv); // NTT
		for(int j=0;j<n;j+=m){
			CD w(1);
			for(int k=j,k2=j+m/2;k2<j+m;k++,k2++){
				CD u=a[k];CD v=a[k2]*w;a[k]=u+v;a[k2]=u-v;w=w*wi;
			}
		}
	}
	if(inv)fore(i,0,n)a[i]/=n; // FFT
	//if(inv){ // NTT
	//	CD z(pm(n,MOD-2)); // pm: modular exponentiation
	//	fore(i,0,n)a[i]=a[i]*z;
	//}
}
poly multiply(poly& p1, poly& p2){
	int n=p1.size()+p2.size()+1;
	int m=1,cnt=0;
	while(m<=n)m+=m,cnt++;
	fore(i,0,m){R[i]=0;fore(j,0,cnt)R[i]=(R[i]<<1)|((i>>j)&1);}
	fore(i,0,m)cp1[i]=0,cp2[i]=0;
	fore(i,0,(int)p1.size())cp1[i]=p1[i];
	fore(i,0,(int)p2.size())cp2[i]=p2[i];
	dft(cp1,m,false);dft(cp2,m,false);
	fore(i,0,m)cp1[i]=cp1[i]*cp2[i];
	dft(cp1,m,true);
	poly res;
	n-=2;
	fore(i,0,n)res.pb((ll)floor(cp1[i].real()+0.5)); // FFT
	//fore(i,0,n)res.pb(cp1[i].x); // NTT
	return res;
}

ll n,x,y,a[MAXN],ed[MAXN],q,ans[MAXN];

void precalc(){
	//do precalc:
    fore(i,1,100){
        if (ed[i]){
            for(ll j = 1; i*j<100; j++) ans[i*j] = i;
        }
    }
}


int main(){
    fast;
    cin>>n>>x>>y;
    fore(i,0,n+1) cin>>a[i];
    
    poly p1((2*x)+1,0);
    fore(i,0,n+1){
        p1[x-a[i]]=1;
        p1[x+a[i]]=1;
    }

    poly p2 = p1;
    poly res = multiply(p1,p2);
    //Existing differences
    vector<ll> vl(1e6 + 1);

    for (int i = 2*x+1; i < (int)res.size(); i++) {
        if (i > 4*x) break;
        if ((i - 2*x)*2 + 2*y >= (1e6 + 1)) break;
        if (res[i] > 0) vl[(i-2*x)*2 + 2*y] = (i-2*x)*2 + 2*y;
    }

    for (int i = 1; i < (int)vl.size(); i++) {
        if (vl[i] == 0) continue;
        for (int j = 1; j*i < (int)vl.size(); j++) {
            vl[i*j] = max(vl[i*j], vl[i]);
        }
    }

    cin>>q;
    while(q--){
		ll k;
        cin>>k;
        if (ans[k] == 0) cout<<-1<<" ";
        else cout<<ans[k]<<" ";
    }
    cout<<nl;
    return 0;
}
