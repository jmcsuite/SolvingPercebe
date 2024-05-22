#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);

using namespace std;

ll n,ans,m;
ll dp[20000005],cont,tams,tamt;
vector <ll> a,b;
string s,t;

void init(){
    a.clear(), a.resize(n);
    b.clear(), b.resize(m);
    s = t = "";
}

vector<int> kmp(vector<ll>& s){
    int n = s.size();
    vector<int> vs(n);

    for(int i=1; i<n; i++){
        int j = vs[i-1];
        while(j!=0 && s[i] != s[j]){
            j = vs[j-1];
        }
        if(s[i] == s[j]) j++;
        vs[i] = j;
    }
    return vs;
}


void preprocess(){
    int i = 0, j = -1;
    dp[0] = -1;
    while (i < tamt){
        while (j >= 0 && (t[i] != t[j])) j = dp[j];
        i++;
        j++;
        dp[i] = j;
    }
}

void kmp(){
    int i = 0, j = 0;
    while(i < tams){
        while (j >= 0 && s[i] != t[j]) j = dp[j];
        i++;
        j++;
        if (j == tamt){
            cont++;
            j = dp[j];
        }
    }
}

int main(){
    fast;
    cin>>n>>m;
    init();
    for (int i = 0; i<n; i++) cin>>a[i];
    for (int i = 0; i<m; i++) cin>>b[i];

    vector<ll> deltas;
    //pattern string:
    for (int i = 1; i<n; i++){
        ll dif = a[i]-a[i-1];
        deltas.push_back(dif);
    } 

    deltas.push_back(100000000000000);
    //base string:
    for (int i = 1; i<m; i++){
        ll dif = b[i]-b[i-1];
        deltas.push_back(dif);
    }   
    if (n == 1){ //pattern of size 1:
        cout<<m<<nl;
        return 0;
    }

    vector<int> vs = kmp(deltas);
    ll ans = 0;
    for(ll x : vs){
        if(x == n-1) ans++;
    }
    cout << ans << '\n';
    //for(int i=0; i<(int)deltas.size(); i++) cout << deltas[i] << ' ';
    //cout << endl;
    //for(ll x: vs) cout << x << ' ' ;
    //cout<<s<<nl;
    //cout<<t<<nl;
    //s += "$";
    //tams = s.size(); //base string
    //tamt = t.size(); //substring target
    //cont = 0;
    //preprocess();
    //kmp();
    //cout<<cont<<nl;
    return 0;
}   
