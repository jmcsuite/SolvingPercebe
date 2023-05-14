#include<bits/stdc++.h>
using namespace std;
///Macros
#define int long long
#define pb push_back
#define fs first
#define sc second
#define pf push_front
#define all(x) x.begin() , x.end()
#define sz(x) (int)(x.size())
#define mid (L+R)/2
//typedef __int128_t int128;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector< pii > vpii;
typedef vector<vi> vvi;
typedef vector<vpii> vvpii;
typedef pair<vi,vi> pvv;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int ui;
///Constraints:
const int inf = ((1ll<<31ll)-1ll);
const long long INF = (((1ll<<60ll)-1ll)*2ll)+1ll;
const ull mod =1000000007;
const ld pi = acos(-1);
const ld eps=1e-12;
/// Functions:
#define lg2(x) 31 - __builtin_clz(x)
#define lg2ll(x) 63ll - __builtin_clzll(x)
#define lgx(x,b) ( log(x) / log(b) )

/*#include<ext/pb_ds/assoc_container.hpp> // Common file
#include<ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
//comenta el define long long int
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order
// order_of_key */
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

/// Quick Pow------------------------------------------------
int  qpow(int a, int b) {
int res = 1;
for (; b; b /= 2, a = (a*a)%mod) {
    if (b % 2) {
        res =(res*a)%mod;
    }
}
    return res;
}
///Inverso Modular
int InverM(int a,int b)
{
    int eso=a-(a/b)*b;
    if(eso==0)
        return 0;
    int ans=(1-b*InverM(b,eso))/eso;
    if(ans<0)
        ans+=b;
    return ans;
}

const int MAXN=(ll)2e7+3;
/// Variables------------------------------------------------
int n,m,q,k;

void problem()
{
    cin>>n>>q;
    vi A(n);
    for(auto &a:A)cin>>a;
    sort(all(A));
    while(q--){
        int k;cin>>k;
        int me,ops;
        if(k%2!=n%2){
           ops=min(n-1,k);
            me=(k-ops)/2;
        }else{
            ops=min(n,k);
            me=(k-ops)/2;
        }
        vi B=A;
        for(int i=0;i<ops;i++){
            B[i]+=k-i;
        }
        sort(all(B));
        int dif=0;
        for(int i=n-1;i>0;i--){
            dif+=B[i]-B[0];
        }
        if(dif>=me){
            cout<<B[0]<<' ';continue;
        }
        me-=dif;
        cout<<B[0]-((me-1)/n+1)<<' ';

    }


}
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.setf(ios::fixed);
    cout.precision(0);
// freopen("a.in","r",stdin);
//  freopen("a.out","w",stdout);
    int tc=1;
   // cin>>tc;
    while(tc--)
    {
        problem();
        cout<<'\n';
    }

}



///Tips
//Busqueda Binaria
//Precomputing
//Dinamic Programming
//Revisar constraints

