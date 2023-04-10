#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=300000;
ll vl[maxn];
ll sum[maxn];
ll sum2[maxn];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N; cin >> N;
        for(int i=0; i<N; i++) cin>>vl[i];
        if(N % 2 != 0){
            cout << "YES\n";
            continue;
        }
        for(int i=0; i<N; i++) sum[i] = sum2[i] = 0;
        for(int i=2; i<N; i++) sum[i] = vl[i-1]-vl[i-2];
        for(int i=N-3; i>=0; i--) sum2[i] = vl[i+2]-vl[i+1];
        for(int i=2; i<N; i+=2) sum[i] += sum[i-2];
        for(int i=N-3; i>=0; i-=2) sum2[i] += sum2[i+2];
        bool se=true;

        
        for(int i=0; i<N; i+=2){
            ll carry = sum[i]+sum2[i+1];
            if(carry < (vl[i]-vl[i+1])) se=false;
        }
        if(se) cout << "YES\n";
        else cout << "NO\n"; /*
        ll ans = 0;
        for(int i=1; i<N; i+=2) ans += vl[i]-vl[i-1];
        if(ans >= 0) cout << "YES\n";
        else cout << "NO\n";*/
    }
}

        
