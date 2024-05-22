#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll mod = 1e9+7;

ll bin_exp(ll a, ll x){
    ll ans = 1;
    while(x > 0){
        if(x%2==1) ans = (ans*a)%mod;
        a = (a*a)%mod;
        x/=2;
    }
    return ans;
}

ll memDP[66][66];

ll dp(ll A, ll B, ll C, ll inA, ll inB, ll inC, ll idx){
    if(idx < 0) return 1;
    if(memDP[idx][inA*4+inB*2+inC]) return memDP[idx][inA*4+inB*2+inC];
    ll ans = 0;
    for(int i = 0; i<2; i++){
        for(int j = 0; j<2; j++){
            for(int k = 0; k<2; k++){
                ll bA = A&(ll(1)<<idx);
                ll bB = B&(ll(1)<<idx);
                ll bC = C&(ll(1)<<idx);
                if(bA) bA = 1;
                if(bB) bB = 1;
                if(bC) bC = 1;

                if(i > bA && inA == 1) continue;
                if(j > bB && inB == 1) continue;
                if(k > bC && inC == 1) continue;
                if((j^k) != i) continue;
                ll ninA = 1;
                ll ninB = 1;
                ll ninC = 1;
                if(inA == 0 || i < bA) ninA=0;
                if(inB == 0 || j < bB) ninB=0;
                if(inC == 0 || k < bC) ninC=0;
                ans = (ans+ll(1)*dp(A,B,C,ninA,ninB,ninC,idx-1))%mod;
            }
        }
    }
    memDP[idx][inA*4+inB*2+inC] = ans;
    return ans;
}

ll get(ll A, ll B, ll C){
    for(int i = 0; i < 66; i++){
        for(int j=0; j<66; j++){
            memDP[i][j] = 0;
        }
    }
    return dp(A,B,C,1,1,1,60);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll bA;ll aA; ll bB; ll aB; ll bC; ll aC;
    cin >> bA >> aA >> bB >> aB >> bC >> aC;
    bA--; bB--; bC--;
    ll cc = get(aA,aB,aC)-get(bA,aB,aC);
    ll pp = get(aA,bB,aC)-get(bA,bB,aC);
    ll dd = get(aA,aB,bC)-get(bA,aB,bC);
    ll nn = get(aA,bB,bC)-get(bA,bB,bC);
    ll ans = (cc-pp-dd+nn)%mod;
    ll pr = ((aA-bA)*(aB-bB))%mod;
    pr = ((pr)*(aC-bC))%mod;
    ll inv = bin_exp(pr,mod-2);
    ans = (pr-ans)%mod;
    ans = (ans*inv)%mod;
    ans = (ans + mod)%mod;
    cout << ans << '\n';
}
