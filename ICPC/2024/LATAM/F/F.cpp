#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 2e5+1;

ll gcd(ll a, ll b){
    if (a == 0) return b;
    if (b == 0) return a;
    return gcd(b%a, a);
}

ll dp[maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N; cin >> N;
    vll vl(N);
    ll g = 0;
    for (int i = 0; i < N; i++) {
        cin >> vl[i]; 
        ll x; cin >> x;
        g = gcd(x,g);
    }
    bool cero = false;
    for (int i=0; i<N; i++) if (vl[i]==0) cero=true;

    map<ll,ll> mp;
    for (int i=0; i<N; i++) mp[vl[i]]++;
    for (int i=0; i<maxn; i++) dp[i]=-1;
    dp[0]=0;
    for(pair<ll,ll> p: mp) {
        for (int i=0; i<maxn; i++) {
            if(dp[i]!=-1) {
                dp[i]=0;
                continue;
            }
            if(p.first > i) continue;
            if(dp[i-p.first] >= 0 && dp[i-p.first] < p.second) dp[i]=dp[i-p.first]+1;
        }
    }


    bool ans = false;
    ll S = 0;
    for (int i=0; i<N; i++) S+=vl[i];
    for (int i=1; i<S; i++) if ((S-2*i)%g == 0 && dp[i]!=-1) ans=true;

    if (N > 1 && cero && S%g==0) ans=true;
    cout << (ans ? "Y\n" : "N\n");
}
