///Giga_Cronos Template from UH Top


#include<bits/stdc++.h>
#pragma GCC optimize("no-stack-protector,unroll-loops", "omit-frame-pointer", "inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma,tune=native")
#pragma GCC option("arch=native", "no-zero-upper") // Enable AVX
using namespace std;
///Macros
#define int long long
#define pb push_back
#define fs first
#define sc second
#define pf push_front
#define all(x) x.begin() , x.end()
#define rall(x) x.rbegin() , x.rend()
#define sz(x) (int)(x.size())
#define mid ((L+R)/2)

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector< pii > vpii;
typedef vector<vi> vvi;
typedef vector<vpii> vvpii;
typedef pair<vi,vi> pvv;
typedef __int128_t int128;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int ui;
///Constraints:
const int inf = ((1ll<<31ll)-1ll);
const long long INF = (((1ll<<60ll)-1ll)*2ll)+1ll;
const ull mod=998'244'353;
const ld pi = acos(-1);
const ld eps=1e-8;

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

int  qpow(int a, int b,int mod) {
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
    int eso=a%b;
    if(eso==0)
        return 0;
    int ans=(1-(int128)b*InverM(b,eso))/eso;
    if(ans<0)
        ans+=b;
    return ans;
}
const int MAXN=200'005;
/// Variables-----------------------------------------------
int n,m,q,k;
void problem()
{
    cin>>n>>k;
    string s;cin>>s;
    vi A;
    for(int i=0;i<n;i++){
        if(s[i]=='1'){
            A.pb(1);
        }else{
            A.pb(-1);
        }
    }  
    vector<int> Ans;
    for(int i=n-1;i>0;i--){
        if(i+1<n)
        A[i]+=A[i+1];
        Ans.pb(A[i]);
    }
    sort(rall(Ans));
    int sum=0;
    for(int i=0;i<n-1;i++){
        sum+=Ans[i];
        if(sum>=k){
            cout<<i+2;
            return;
        }
    }
    cout<<-1;

}
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.setf(ios::fixed);
    cout.precision(12);
  //  freopen("a.in","r",stdin);
  //  freopen("a.out","w",stdout);
    
    int tc=1;
    cin>>tc;
    while(tc--)
    {
        problem();
        cout<<'\n';
    }

}
